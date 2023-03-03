module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [ "dst/cosmopolitan.h",
    (Digest.of_hex "51c2a46bb28532ae57ee8b9fe273fa0087650bc2f30a145668ed7a6117eb418d")
  ; "dst/ape.lds",
    (Digest.of_hex "80eede1e50807555f44ea63183cb25dc99d499f6b2ce0f393845d6c4e60ede09")
  ; "dst/crt.o",
    (Digest.of_hex "c08c7a83426e4fd19dfcf9815830fb7b4ce5a61ba5b9ed4a520585bb3481e71e")
  ; "dst/ape.o",
    (Digest.of_hex "4fa4fde9c929c826c9b2f069fc30622c3da2086d4a969cdda750535174391286")
  ; "dst/ape-no-modify-self.o",
    (Digest.of_hex "d9c8687860409f1b6a3b1c5d2cea614371055247ebcdd48ec3b5bf23d2660f16")
  ; "dst/cosmopolitan.a",
    (Digest.of_hex "5f2478cf995cc11c90c166e8a7b1e0935bc9b928c8eefc581006f34f41dd31a6")
  ; "dst/ape-copy-self.o",
    (Digest.of_hex "334c4ec80c3a4397b878efd6cf57285b25cda885976baee7aacb00d7267241e7") ]

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
