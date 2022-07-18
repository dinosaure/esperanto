module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [ "dst/cosmopolitan.h",
    (Digest.of_hex "ba55ae9b3795b66998b5587ed358abdc8da8cb1ea20164ad7b55d66c552dba0c")
  ; "dst/ape.lds",
    (Digest.of_hex "63d6f89cf4cdf4aa8068c5db6475a4e2da4824470944957f214f7cf3d0f6878f")
  ; "dst/crt.o",
    (Digest.of_hex "45b97b158e1e234fce927379c2ffa64e45bb84ea894ec6c64e1e17f9da515691")
  ; "dst/ape.o",
    (Digest.of_hex "7995b4d6611a01d43a3b6a2a793be3bcecaada60c2eae0b2dddb6ef42b242086")
  ; "dst/ape-no-modify-self.o",
    (Digest.of_hex "fb262ad511b7bcf25e32e40a92bf0967d491fe8cfbe57e2b9178a33402224477")
  ; "dst/cosmopolitan.a",
    (Digest.of_hex "136047470d91b235c5d6204d2938f2da6219504e9bf636a6ef4debd67895744c") ]

let digest filename =
  let tmp = Bytes.create 0x1000 in
  let rec digest ic acc = match input ic tmp 0 (Bytes.length tmp) with
    | 0 -> Digest.get acc
    | exception End_of_file -> Digest.get acc
    | len ->
      digest ic (Digest.feed_bytes acc ~off:0 ~len tmp) in
  let ic = open_in filename in
  let hash = digest ic Digest.empty in
  close_in ic ; hash

let extract filename dst =
  let ic = Zip.open_in filename in
  let entries = Zip.entries ic in
  let rec go acc = function
    | [] -> List.rev acc
    | entry :: rest ->
      let filename = dst / entry.Zip.filename in
      Zip.copy_entry_to_file ic entry filename ;
      go (filename :: acc) rest in
  let files = go [] entries in
  Zip.close_in ic ;
  files

let verify bindings =
  let a = List.sort (fun (k0, _) (k1, _) -> String.compare k0 k1) bindings in
  let b = List.sort (fun (k0, _) (k1, _) -> String.compare k0 k1) expected in
  a = b 

let () = match Sys.argv with
  | [| _; "list" |] ->
    List.iter (fun (filename, _) -> Fmt.pr "%s\n%!" filename) expected
  | [| _; zip; dst; |] when Sys.file_exists zip ->
    if Sys.file_exists dst && not (Sys.is_directory dst)
    then Fmt.failwith "%s already exists and it is not a directory" dst ;
    if not (Sys.file_exists dst) then Sys.mkdir dst 0o700 ;
    let files = extract zip dst in
    let hashes = List.map digest files in
    let bindings = List.combine files hashes in
    if verify bindings
    then exit 0 else exit 1
  | _ -> Fmt.epr "%s [cosmopolitan.zip <directory>|list]\n%!" Sys.argv.(0)
