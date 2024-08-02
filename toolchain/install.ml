module Digest = Digestif.SHA256

let ( / ) = Filename.concat
let () = assert (Filename.dir_sep = "/")
let () = Printexc.record_backtrace true
let pr fmt = Format.printf fmt
let failwith fmt = Format.kasprintf failwith fmt
let invalid_arg fmt = Format.kasprintf invalid_arg fmt
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

let dfs graph visited start_node =
  let rec explore path visited node =
    if List.mem node path then failwith "Cycle found"
    else if List.mem node visited then visited
    else
      let new_path = node :: path in
      let edges = List.assoc node graph in
      let visited = List.fold_left (explore new_path) visited edges in
      node :: visited
  in
  explore [] visited start_node

let topo : ('a * 'a list) list -> 'a list =
 fun graph ->
  List.fold_left (fun visited (node, _) -> dfs graph visited node) [] graph

let normalize path =
  let norm segs =
    let rec go acc = function
      | "." :: [] -> acc
      | "." :: rest -> go acc rest
      | ".." :: rest -> (
          match acc with
          | ".." :: _ | [] -> go (".." :: acc) rest
          | _seg :: acc -> ( match rest with [] -> acc | rest -> go acc rest))
      | seg :: rest -> go (seg :: acc) rest
      | [] -> ( match acc with ".." :: _ -> acc | [] -> [] | acc -> acc)
    in
    List.rev (go [] segs)
  in
  let segs = String.split_on_char '/' path in
  String.concat Filename.dir_sep (norm segs)

let cuts ~sep str =
  let sep_len = String.length sep in
  if sep_len = 0 then invalid_arg "cuts";
  let str_len = String.length str in
  let max_sep_idx = sep_len - 1 in
  let max_str_idx = str_len - sep_len in
  let add str ~start ~stop acc =
    if start = stop then String.empty :: acc
    else String.sub str start (stop - start) :: acc
  in
  let rec check_sep start i k acc =
    if k > max_sep_idx then
      let new_start = i + sep_len in
      scan new_start new_start (add str ~start ~stop:i acc)
    else if str.[i + k] = sep.[k] then check_sep start i (k + 1) acc
    else scan start (i + 1) acc
  and scan start i acc =
    if i > max_str_idx then
      if start = 0 then [ str ] else List.rev (add str ~start ~stop:str_len acc)
    else if str.[i] = sep.[0] then check_sep start i 1 acc
    else scan start (i + 1) acc
  in
  scan 0 0 []

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

let copy ?(exec = false) ~src dst =
  let ctx = Digest.empty in
  let buf = Bytes.create 0x1000 in
  let ic = open_in src and oc = open_out dst in
  let rec go ctx =
    match input ic buf 0 (Bytes.length buf) with
    | 0 -> Digest.get ctx
    | len ->
        let ctx = Digest.feed_bytes ctx buf ~off:0 ~len in
        output_substring oc (Bytes.unsafe_to_string buf) 0 len;
        go ctx
  in
  let hash = go ctx in
  close_in ic;
  close_out oc;
  if exec then Unix.chmod dst 0o744;
  hash

let link ~src ~dst =
  let old = Unix.getcwd () in
  let lnk = Unix.readlink src in
  Unix.chdir (Filename.dirname dst);
  Unix.symlink lnk (Filename.basename dst);
  let hash = hash_of_filename lnk in
  Unix.chdir old;
  hash

type action =
  | Copy of { exec : bool; src : string; dst : string }
  | Link of { src : string; dst : string }

let deps lnks =
  let tbl = Hashtbl.create 0x100 in
  let g = Hashtbl.create 0x100 in
  let collect = function
    | Link { src; dst } as action ->
        let lnk = Unix.readlink src in
        let dep = normalize (Filename.dirname dst / lnk) in
        Hashtbl.add tbl dst (action, dep)
    | _ -> ()
  in
  let add g lnk revdep =
    try
      let vs = Hashtbl.find g lnk in
      Hashtbl.replace g lnk (revdep :: vs)
    with _ -> Hashtbl.add g lnk [ revdep ]
  in
  let fold _ (lnk, dep) =
    match Hashtbl.find tbl dep with
    | revdep, _ -> add g lnk revdep
    | exception Not_found -> Hashtbl.add g lnk []
  in
  List.iter collect lnks;
  Hashtbl.iter fold tbl;
  Hashtbl.fold (fun k v acc -> (k, v) :: acc) g []

let do_action ~dst:sep tbl = function
  | Copy { exec; src; dst } ->
      pr " INSTALL %s\n%!" (Filename.basename src);
      mkdir (Filename.dirname dst);
      let hash = copy ~exec ~src dst in
      let[@warning "-8"] ("" :: src) = cuts ~sep:(sep ^ Filename.dir_sep) src in
      let src = String.concat (sep ^ Filename.dir_sep) src in
      if Hashtbl.find tbl src = hash = false then (
        pr " HASH %s %a %a\n%!" src Digest.pp (Hashtbl.find tbl src) Digest.pp
          hash;
        assert false)
  | Link { src; dst } ->
      pr " SYMLINK %s\n%!" (Filename.basename src);
      mkdir (Filename.dirname dst);
      let hash = link ~src ~dst in
      let[@warning "-8"] ("" :: src) = cuts ~sep:(sep ^ Filename.dir_sep) src in
      let src = String.concat (sep ^ Filename.dir_sep) src in
      if Hashtbl.find tbl src = hash = false then (
        pr " HASH %s %a %a\n%!" src Digest.pp (Hashtbl.find tbl src) Digest.pp
          hash;
        assert false)

let copy prefix dst src =
  let stat = Unix.lstat src in
  let path =
    match cuts ~sep:dst src with
    | "" :: path -> String.concat dst path
    | _ -> src
  in
  match stat.Unix.st_kind with
  | Unix.S_REG ->
      let exec = stat.st_perm land 0o100 <> 0 in
      Copy { exec; src; dst = prefix / path }
  | Unix.S_LNK -> Link { src; dst = prefix / path }
  | _ -> failwith "Invalid file: %S" path

let files_of_directory dst =
  let dir ~current (acc, to_traverse) entry =
    let p = current / entry in
    if Sys.is_directory p then (acc, p :: to_traverse)
    else (p :: acc, to_traverse)
  in
  let rec go acc = function
    | (x :: r) :: up ->
        let entries = Sys.readdir x in
        let acc, to_traverse =
          Array.fold_left (dir ~current:x) (acc, []) entries
        in
        go acc (to_traverse :: r :: up)
    | [] :: [] -> acc
    | [] :: up -> go acc up
    | _ -> assert false
  in
  let init (acc, to_traverse) p =
    if Sys.is_directory p then (acc, p :: to_traverse)
    else (p :: acc, to_traverse)
  in
  let acc, to_traverse = List.fold_left init ([], []) [ dst ] in
  go acc (to_traverse :: [])

let collect digest =
  let tbl = Hashtbl.create 0x100 in
  let rec go ic =
    match input_line ic with
    | line ->
        let[@warning "-8"] (hash :: filename :: _) =
          String.split_on_char ' ' line
        in
        let hash = Digest.of_hex hash in
        Hashtbl.add tbl filename hash;
        go ic
    | exception End_of_file -> ()
  in
  let ic = open_in digest in
  go ic;
  close_in ic;
  tbl

let is_link = function Link _ -> true | _ -> false

let install dst digest prefix =
  let oracle = collect digest in
  let files = files_of_directory dst in
  let actions = List.map (copy prefix dst) files in
  let files, links = List.partition (Fun.negate is_link) actions in
  List.iter (do_action ~dst oracle) files;
  List.iter (do_action ~dst oracle) (List.rev (topo (deps links)))

let dst = ref "dst"
let digest = ref "cosmocc.digest"
let prefix = ref "/usr/local/"

let spec =
  [
    ( "-d",
      Arg.Set_string dst,
      "The directory to which where are extracted files." );
    ("--prefix", Arg.Set_string prefix, "A prefix of where are located sources.");
    ( "--digest",
      Arg.Set_string digest,
      "The oracle to verify the integrity of the cosmocc distribution." );
  ]

let anonymous_argument str = invalid_arg "Unexpected anonymous argument: %S" str

let usage =
  Format.asprintf
    "%s [-d <directory>] [--prefix <directory>] [--digest <filename>]\n%!"
    Sys.argv.(0)

let () =
  Arg.parse spec anonymous_argument usage;
  install !dst !digest !prefix
