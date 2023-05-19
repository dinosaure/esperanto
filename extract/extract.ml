module Digest = Digestif.SHA256

let ( / ) = Filename.concat

let expected =
  [
    ( "dst/cosmopolitan.h",
      Digest.of_hex
        "902ab6536e2659922a17f281d06205022e423c144451360c225abf432145cbf3" );
    ( "dst/ape.lds",
      Digest.of_hex
        "dc81d22b81568915d2adb04cb2782039cf37b092ae2141fb505ef97cb5315a9c" );
    ( "dst/crt.o",
      Digest.of_hex
        "c08c7a83426e4fd19dfcf9815830fb7b4ce5a61ba5b9ed4a520585bb3481e71e" );
    ( "dst/ape.o",
      Digest.of_hex
        "82b09c5ae5902e6678a81d9e38d529bccd7c6eadbfd44a514af7b50c2c349624" );
    ( "dst/ape-no-modify-self.o",
      Digest.of_hex
        "972af36df1217a913d37bd66fee37794cb9216b58656a792ff3fb2711a037199" );
    ( "dst/cosmopolitan.a",
      Digest.of_hex
        "04fc05384e57589dad8bd3309e1ebfa254a937b8427a76e06a0b6ed1fc815fec" );
    ( "dst/ape-copy-self.o",
      Digest.of_hex
        "b7d61413eb31db8082943669cd5e4f23b0b4177b4fba6a2b1db39a8bc42447e8" );
  ]

let digest filename =
  let tmp = Bytes.create 0x1000 in
  let rec digest ic acc =
    match input ic tmp 0 (Bytes.length tmp) with
    | 0 -> Digest.get acc
    | exception End_of_file -> Digest.get acc
    | len -> digest ic (Digest.feed_bytes acc ~off:0 ~len tmp)
  in
  let ic = open_in filename in
  let hash = digest ic Digest.empty in
  close_in ic;
  hash

let extract filename dst =
  let ic = Zip.open_in filename in
  let entries = Zip.entries ic in
  let rec go acc = function
    | [] -> List.rev acc
    | entry :: rest ->
        let filename = dst / entry.Zip.filename in
        Zip.copy_entry_to_file ic entry filename;
        go (filename :: acc) rest
  in
  let files = go [] entries in
  Zip.close_in ic;
  files

let verify bindings =
  let a = List.sort (fun (k0, _) (k1, _) -> String.compare k0 k1) bindings in
  let b = List.sort (fun (k0, _) (k1, _) -> String.compare k0 k1) expected in
  a = b

let () =
  match Sys.argv with
  | [| _; "list" |] ->
      List.iter (fun (filename, _) -> Fmt.pr "%s\n%!" filename) expected
  | [| _; zip; dst |] when Sys.file_exists zip ->
      if Sys.file_exists dst && not (Sys.is_directory dst) then
        Fmt.failwith "%s already exists and it is not a directory" dst;
      if not (Sys.file_exists dst) then Sys.mkdir dst 0o700;
      let files = extract zip dst in
      let hashes = List.map digest files in
      let bindings = List.combine files hashes in
      if verify bindings then exit 0 else exit 1
  | _ -> Fmt.epr "%s [cosmopolitan.zip <directory>|list]\n%!" Sys.argv.(0)
