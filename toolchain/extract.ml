module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [ "dst/cosmopolitan.h",
    (Digest.of_hex "bc5c3d52214eb744d0dbdba95c628b8c53a53efacc558cd36f60c1d585e60e36")
  ; "dst/ape.lds",
    (Digest.of_hex "bcd87c737408ab18a6d4ffce2848a6bbf3cf2e8df904fa3aac475d11a1f938f3")
  ; "dst/crt.o",
    (Digest.of_hex "d4874eaed8fe78ea8745cd3acc66e8eb7ccf2ba2d296aed64f878528b45e2d9b")
  ; "dst/ape.o",
    (Digest.of_hex "7e8d302fd5654235ebebc5a94ab1a22437b90164032d4304ac55729755bc7f5d")
  ; "dst/ape-no-modify-self.o",
    (Digest.of_hex "1ed036a5d9d7d56d473874bcde93901717a71e2f4502f605b1e70913023fadd8")
  ; "dst/cosmopolitan.a",
    (Digest.of_hex "50ae3c76998007ba0a6626dc33f33d387cf12da6261dafb7e05d287bcc656ca4") ]

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
