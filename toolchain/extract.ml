module Digest = Digestif.SHA256

let ( / ) = Filename.concat
let () = assert (Filename.dir_sep = "/")
let is_directory path = Sys.file_exists path && Sys.is_directory path

let mkdir path =
  let segments = String.split_on_char '/' path in
  let rec go current = function
    | [] -> ()
    | hd :: tl ->
        let current = String.concat Filename.dir_sep [ current; hd ] in
        if is_directory current then go current tl
        else
          let () = Sys.mkdir current 0o755 in
          go current tl
  in
  if is_directory path = false then
    match segments with "" :: _ -> go "/" segments | _ -> go "." segments

let extract filename dst =
  let ic = Zip.open_in filename in
  let entries = Zip.entries ic in
  let rec go acc = function
    | [] -> List.rev acc
    | entry :: rest ->
        Format.printf " UNZIP %s\n%!" (Filename.basename entry.Zip.filename);
        let filename = dst / entry.Zip.filename in
        mkdir (Filename.dirname filename);
        if entry.Zip.is_directory = false then
          let op = Zip.copy_entry_to_file ic entry filename in
          go ((filename, op) :: acc) rest
        else (
          mkdir filename;
          go acc rest)
  in
  let ops = go [] entries in
  Zip.close_in ic;
  ops

let hash_of_filename filename =
  let ic = open_in filename in
  let buf = Bytes.create 0x1000 in
  let rec go ctx =
    match input ic buf 0 (Bytes.length buf) with
    | 0 -> Digest.get ctx
    | len -> go (Digest.feed_bytes ctx buf ~off:0 ~len)
  in
  let hash = go Digest.empty in
  close_in ic;
  hash

let do_operation = function
  | filename, `File hash -> (filename, hash)
  | filename, `Symlink src ->
      let old = Unix.getcwd () in
      Unix.chdir (Filename.dirname filename);
      Unix.symlink src (Filename.basename filename);
      let hash = hash_of_filename src in
      Unix.chdir old;
      (filename, hash)

let verify oracle dst files_and_hashes =
  let rec go acc ic =
    match input_line ic with
    | line ->
        let[@warning "-8"] (hash :: filename :: _) =
          String.split_on_char ' ' line
        in
        let hash = Digest.of_hex hash in
        go ((dst / filename, hash) :: acc) ic
    | exception End_of_file -> List.rev acc
  in
  let ic = open_in oracle in
  let files_and_hashes' = go [] ic in
  close_in ic;
  let compare (f0, _) (f1, _) = String.compare f0 f1 in
  let files_and_hashes = List.sort compare files_and_hashes in
  let files_and_hashes' = List.sort compare files_and_hashes' in
  files_and_hashes = files_and_hashes'

let output dst oracle =
  let first = ref true in
  let rec go ic =
    match input_line ic with
    | line ->
        let[@warning "-8"] (_hash :: filename :: _) =
          String.split_on_char ' ' line
        in
        if not !first then Format.printf " ";
        first := false;
        Format.printf "%s" (dst / filename);
        go ic
    | exception End_of_file -> Format.printf "\n%!"
  in
  let ic = open_in oracle in
  go ic;
  close_in ic

let dst = ref "dst"
let digest = ref "cosmocc.digest"
let zip = ref "cosmocc.zip"
let list = ref false

let spec =
  [
    ("-d", Arg.Set_string dst, "A directory to which to extract files.");
    ( "--digest",
      Arg.Set_string digest,
      "The oracle to verify the integrity of the cosmocc distribution." );
  ]

let anonymous_argument = function "list" -> list := true | str -> zip := str

let usage =
  Format.asprintf "%s [-d <directory>] [--digest <filename>] <zip>\n%!"
    Sys.argv.(0)

let () =
  Arg.parse spec anonymous_argument usage;
  if !list then output !dst !digest
  else
    let operations = extract !zip !dst in
    let files_and_hashes = List.map do_operation operations in
    assert (verify !digest !dst files_and_hashes)
