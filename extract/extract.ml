module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [ "dst/cosmopolitan.h",
    (Digest.of_hex "c14dc385e73ab4841bdb91cd44899797a3d38613218bc4465b08e6ab9560b3de")
  ; "dst/ape.lds",
    (Digest.of_hex "23b3fe457a2f16290890445462697b3369b9789a2d08f2f9a9ea0e715ecc02a3")
  ; "dst/crt.o",
    (Digest.of_hex "45b97b158e1e234fce927379c2ffa64e45bb84ea894ec6c64e1e17f9da515691")
  ; "dst/ape.o",
    (Digest.of_hex "83fbbcb4dbb5c96a0f77b5e7dc6f5e1ee8cac1c59dab5029a3d0b3154c87783c")
  ; "dst/ape-no-modify-self.o",
    (Digest.of_hex "302928befaf13e44e05ecc1f51343966cb5d66deddcf002fd0d35b651ed178d0")
  ; "dst/cosmopolitan.a",
    (Digest.of_hex "bcd3e79666cf9324b62733eaae12070b65b62feee0b40aa15c0d891b628ba261") ]

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
