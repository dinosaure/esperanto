let dfs graph visited start_node = 
  let rec explore path visited node = 
    if List.mem node path    then assert false else
    if List.mem node visited then visited else     
      let new_path = node :: path in 
      let edges    = List.assoc node graph in
      let visited  = List.fold_left (explore new_path) visited edges in
      node :: visited
  in explore [] visited start_node

let toposort graph = 
  List.fold_left (fun visited (node,_) -> dfs graph visited node) [] graph

let () =
  Fmt.pr "@[<hov>%a@]" Fmt.(Dump.list string)
    (toposort [ ("A", [ "C" ]); ("B", []); ("C", [ "B" ]) ])
