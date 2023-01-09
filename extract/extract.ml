module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [ "dst/cosmopolitan.h",
    (Digest.of_hex "8343e36ca67a616bbb06e86bf6faf8e3e98baac93184c55b3e8515708d864dd7")
  ; "dst/ape.lds",
    (Digest.of_hex "ef8f58405b738e22979b3b271179107322c537f883d830ef220c084b82cd9334")
  ; "dst/crt.o",
    (Digest.of_hex "33c5df0a9c53cbaa2b64e5c1cd7d97a6c0b8b3767621d6f98562e74b2fbd2a8c")
  ; "dst/ape.o",
    (Digest.of_hex "8e52a3a8f46dd40f67bb24944d91165f853e6c8703a3ef7b9dafcd83beb9a8a0")
  ; "dst/ape-no-modify-self.o",
    (Digest.of_hex "c733b326abf8d1521affa679332eac83ed05f822babb86467b7a8b35dd442e1a")
  ; "dst/cosmopolitan.a",
    (Digest.of_hex "feca2c30dc55be7de1a4282bd7c954c8839b7118f3ec1348f96f0b543c442fb6")
  ; "dst/ape-copy-self.o",
    (Digest.of_hex "16b3b7b1f7803b9820348ec199a56446ece17b4d7412cf920701c272edd92eeb") ]

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
