#light

module Functions


let rec neighbors x E = 
  match E with
  | []                               -> []
  | (src,dest,cost)::tl when src = x -> dest :: neighbors x tl
  | hd::tl                           -> neighbors x tl


let rec isEdge x y E = 
  match E with
 | []                                               -> false
 | (src, dest, cost) :: tl when src = x && dest = y -> true
 | (src, dest, cost) :: tl                          -> isEdge x y tl
  


let rec isPath x y V E = 
  match V E with
 | []               -> false
 | (isEdge (x y V)) 
 | (List.exists (fun v -> ((isEdge x v E) && (isPath v y V E )) V))
