let () =
  let tmp = Bytes.create 0x1000 in
  let rec go () = match input stdin tmp 0 (Bytes.length tmp) with
    | 0 -> ()
    | len -> output stdout tmp 0 len ; go ()
    | exception End_of_file -> () in
  go ()
