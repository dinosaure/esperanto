(***********************************************************************)
(*                                                                     *)
(*                         The CamlZip library                         *)
(*                                                                     *)
(*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         *)
(*                                                                     *)
(*  Copyright 2001 Institut National de Recherche en Informatique et   *)
(*  en Automatique.  All rights reserved.  This file is distributed    *)
(*  under the terms of the GNU Lesser General Public License, with     *)
(*  the special exception on linking described in file LICENSE.        *)
(*                                                                     *)
(***********************************************************************)

exception Error of string * string * string

let read1 = input_byte
let read2 ic =
  let lb = read1 ic in let hb = read1 ic in lb lor (hb lsl 8)
let read4 ic =
  let lw = read2 ic in let hw = read2 ic in
  Int32.logor (Int32.of_int lw) (Int32.shift_left (Int32.of_int hw) 16)
let read4_int ic =
  let lw = read2 ic in let hw = read2 ic in
  if hw > max_int lsr 16 then raise (Error("", "", "32-bit data too large"));
  lw lor (hw lsl 16)
let readstring ic n =
  let s = Bytes.create n in
  really_input ic s 0 n; Bytes.unsafe_to_string s

let write1 = output_byte
let write2 oc n =
  write1 oc n; write1 oc (n lsr 8)
let write4 oc n =
  write2 oc (Int32.to_int n);
  write2 oc (Int32.to_int (Int32.shift_right_logical n 16))
let write4_int oc n =
  write2 oc n;
  write2 oc (n lsr 16)
let writestring oc s =
  output_string oc s

type compression_method = Stored | Deflated

type entry =
  { filename: string;
    extra: string;
    comment: string;
    methd: compression_method;
    mtime: float;
    crc: int32;
    uncompressed_size: int;
    compressed_size: int;
    is_directory: bool;
    file_offset: int64 }

type in_file =
  { if_filename: string;
    if_channel: Stdlib.in_channel;
    if_entries: entry list;
    if_directory: (string, entry) Hashtbl.t;
    if_comment: string }

let entries ifile = ifile.if_entries
let comment ifile = ifile.if_comment

type out_file =
  { of_filename: string;
    of_channel: Stdlib.out_channel;
    mutable of_entries: entry list;
    of_comment: string }

(* Return the position of the last occurrence of [pattern] in [buf],
   or -1 if not found. *)

let strrstr (pattern: string) (buf: bytes) ofs len =
  let rec search i j =
    if i < ofs then -1
    else if j >= String.length pattern then i
    else if String.get pattern j = Bytes.get buf (i + j) then search i (j+1)
    else search (i-1) 0
  in search (ofs + len - String.length pattern) 0

(* Determine if a file name is a directory (ends with /) *)

let filename_is_directory name =
  String.length name > 0 && name.[String.length name - 1] = '/'

(* Read end of central directory record *)

let read_ecd filename ic =
  let buf = Bytes.create 256 in
  let filelen = LargeFile.in_channel_length ic in
  let rec find_ecd pos len =
    (* On input, bytes 0 ... len - 1 of buf reflect what is at pos in ic *)
    if pos <= 0L || Int64.sub filelen pos >= 0x10000L then
      raise (Error(filename, "",
                   "end of central directory not found, not a ZIP file"));
    let toread = if pos >= 128L then 128 else Int64.to_int pos in
    (* Make room for "toread" extra bytes, and read them *)
    Bytes.blit buf 0 buf toread (256 - toread);
    let newpos = Int64.(sub pos (of_int toread)) in
    LargeFile.seek_in ic newpos;
    really_input ic buf 0 toread;
    let newlen = min (toread + len) 256 in
    (* Search for magic number *)
    let ofs = strrstr "PK\005\006" buf 0 newlen in
    if ofs < 0 || newlen < 22 ||
       (let comment_len =
              (Char.code (Bytes.get buf (ofs + 20)))
          lor ((Char.code (Bytes.get buf (ofs + 21))) lsl 8) in
        Int64.(add newpos (of_int (ofs + 22 + comment_len))) <> filelen) then
      find_ecd newpos newlen
    else
      Int64.(add newpos (of_int ofs)) in
  LargeFile.seek_in ic (find_ecd filelen 0);
  let magic = read4 ic in
  let disk_no = read2 ic in
  let cd_disk_no = read2 ic in
  let _disk_entries = read2 ic in
  let cd_entries = read2 ic in
  let cd_size = read4 ic in
  let cd_offset = read4 ic in
  let comment_len = read2 ic in
  let comment = readstring ic comment_len in
  assert (magic = Int32.of_int 0x06054b50);
  if disk_no <> 0 || cd_disk_no <> 0 then
    raise (Error(filename, "", "multi-disk ZIP files not supported"));
  (cd_entries, cd_size, cd_offset, comment)

(* Read central directory *)

let int64_of_uint32 n =
  Int64.(logand (of_int32 n) 0xFFFF_FFFFL)

let read_cd filename ic cd_entries cd_offset cd_bound =
  let cd_bound = int64_of_uint32 cd_bound in
  try
    LargeFile.seek_in ic (int64_of_uint32 cd_offset);
    let e = ref [] in
    let entrycnt = ref 0 in
    while (LargeFile.pos_in ic < cd_bound) do
      incr entrycnt;
      let magic = read4 ic in
      let _version_made_by = read2 ic in
      let _version_needed = read2 ic in
      let flags = read2 ic in
      let methd = read2 ic in
      let _lastmod_time = read2 ic in
      let _lastmod_date = read2 ic in
      let crc = read4 ic in
      let compr_size = read4_int ic in
      let uncompr_size = read4_int ic in
      let name_len = read2 ic in
      let extra_len = read2 ic in
      let comment_len = read2 ic in
      let _disk_number = read2 ic in
      let _internal_attr = read2 ic in
      let _external_attr = read4 ic in
      let header_offset = int64_of_uint32 (read4 ic) in
      let name = readstring ic name_len in
      let extra = readstring ic extra_len in
      let comment = readstring ic comment_len in
      if magic <> Int32.of_int 0x02014b50 then
        raise (Error(filename, name,
                     "wrong file header in central directory"));
      if flags land 1 <> 0 then
        raise (Error(filename, name, "encrypted entries not supported"));

      e := { filename = name;
             extra = extra;
             comment = comment;
             methd = (match methd with
                         0 -> Stored
                       | 8 -> Deflated
                       | _ -> raise (Error(filename, name,
                                           "unknown compression method")));
             mtime = 0.; (* XXX(dinosaure): remove unix dependency *)
             crc = crc;
             uncompressed_size = uncompr_size;
             compressed_size = compr_size;
             is_directory = filename_is_directory name;
             file_offset = header_offset
           } :: !e
    done;
    assert((cd_bound = (LargeFile.pos_in ic)) &&
           (cd_entries = 65535 || cd_entries = !entrycnt land 0xffff));
    List.rev !e
  with End_of_file ->
    raise (Error(filename, "", "end-of-file while reading central directory"))

(* Open a ZIP file for reading *)

let open_in filename =
  let ic = Stdlib.open_in_bin filename in
  try
    let (cd_entries, cd_size, cd_offset, cd_comment) = read_ecd filename ic in
    let entries =
      read_cd filename ic cd_entries cd_offset (Int32.add cd_offset cd_size) in
    let dir = Hashtbl.create (cd_entries / 3) in
    List.iter (fun e -> Hashtbl.add dir e.filename e) entries;
    { if_filename = filename;
      if_channel = ic;
      if_entries = entries;
      if_directory = dir;
      if_comment = cd_comment }
  with exn ->
    Stdlib.close_in ic; raise exn

(* Close a ZIP file opened for reading *)

let close_in ifile =
  Stdlib.close_in ifile.if_channel

(* Return the info associated with an entry *)

let find_entry ifile name =
  Hashtbl.find ifile.if_directory name

(* Position on an entry *)

let goto_entry ifile e =
  try
    let ic = ifile.if_channel in
    LargeFile.seek_in ic e.file_offset;
    let magic = read4 ic in
    let _version_needed = read2 ic in
    let _flags = read2 ic in
    let _methd = read2 ic in
    let _lastmod_time = read2 ic in
    let _lastmod_date = read2 ic in
    let _crc = read4 ic in
    let _compr_size = read4_int ic in
    let _uncompr_size = read4_int ic in
    let filename_len = read2 ic in
    let extra_len = read2 ic in
    if magic <> Int32.of_int 0x04034b50 then
       raise (Error(ifile.if_filename, e.filename, "wrong local file header"));
    (* Could validate information read against directory entry, but
       what the heck *)
    LargeFile.seek_in ifile.if_channel
      (Int64.add e.file_offset (Int64.of_int (30 + filename_len + extra_len)))
  with End_of_file ->
    raise (Error(ifile.if_filename, e.filename, "truncated local file header"))

let read_entry ifile e =
  try
    goto_entry ifile e;
    let res = Bytes.create e.uncompressed_size in
    match e.methd with
      Stored ->
        if e.compressed_size <> e.uncompressed_size then
          raise (Error(ifile.if_filename, e.filename,
                       "wrong size for stored entry"));
        really_input ifile.if_channel res 0 e.uncompressed_size;
        Bytes.unsafe_to_string res
    | Deflated ->
        let in_avail = ref e.compressed_size in
        let out_pos = ref 0 in
        let tmp = Bytes.create 0x1000 in
        let itmp = Bigstringaf.create 0x1000 in
        let otmp = Bigstringaf.create 0x1000 in
        let w = De.make_window ~bits:15 in
        let result =
          De.Higher.uncompress ~w
            ~refill:(fun buf ->
              let read = input ifile.if_channel tmp 0
                               (min !in_avail (Bytes.length tmp)) in
              Bigstringaf.blit_from_bytes tmp ~src_off:0 buf ~dst_off:0 ~len:read ;
              in_avail := !in_avail - read;
              read)
            ~flush:(fun buf len ->
              let buf' = Bigstringaf.substring buf ~off:0 ~len in
              if !out_pos + len > Bytes.length res then
                raise (Error(ifile.if_filename, e.filename,
                             "wrong size for deflated entry (too much data)"));
              Bytes.blit_string buf' 0 res !out_pos len;
              out_pos := !out_pos + len) itmp otmp in
        begin match result with
        | Ok () -> ()
        | Error (`Msg err) -> raise (Error(ifile.if_filename, e.filename, err))
        end;
        if !out_pos <> Bytes.length res then
          raise (Error(ifile.if_filename, e.filename,
                       "wrong size for deflated entry (not enough data)"));
        Bytes.unsafe_to_string res
  with End_of_file ->
    raise (Error(ifile.if_filename, e.filename, "truncated data"))

(* Write the contents of an entry into an out channel *)

let copy_entry_to_channel ifile e oc =
  try
    goto_entry ifile e;
    match e.methd with
      Stored ->
        if e.compressed_size <> e.uncompressed_size then
          raise (Error(ifile.if_filename, e.filename,
                       "wrong size for stored entry"));
        let buf = Bytes.create 4096 in
        let rec copy n =
          if n > 0 then begin
            let r = input ifile.if_channel buf 0 (min n (Bytes.length buf)) in
            output oc buf 0 r;
            copy (n - r)
          end in
        copy e.uncompressed_size
    | Deflated ->
        let in_avail = ref e.compressed_size in
        let tmp = Bytes.create 0x1000 in
        let itmp = Bigstringaf.create 0x1000 in
        let otmp = Bigstringaf.create 0x1000 in
        let w = De.make_window ~bits:15 in
        let result =
          De.Higher.uncompress ~w
            ~refill:(fun buf ->
              let read = input ifile.if_channel tmp 0
                               (min !in_avail (Bytes.length tmp)) in
              Bigstringaf.blit_from_bytes tmp ~src_off:0 buf ~dst_off:0 ~len:read ;
              in_avail := !in_avail - read;
              read)
            ~flush:(fun buf len ->
              let buf' = Bigstringaf.substring buf ~off:0 ~len in
              output_string oc buf') itmp otmp in
        begin match result with
        | Ok () -> ()
        | Error (`Msg err) -> raise (Error(ifile.if_filename, e.filename, err))
        end
  with End_of_file ->
    raise (Error(ifile.if_filename, e.filename, "truncated data"))

(* Write the contents of an entry to a file *)

let copy_entry_to_file ifile e outfilename =
  let oc = open_out_bin outfilename in
  try
    copy_entry_to_channel ifile e oc;
    close_out oc;
  with x ->
    close_out oc;
    Sys.remove outfilename;
    raise x
