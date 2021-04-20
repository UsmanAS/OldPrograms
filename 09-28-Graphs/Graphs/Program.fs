#light

open Functions

//
// main() program:  when you run as an .exe
//
[<EntryPoint>]
let main argv =
  let V = 
    ["A"; "B"; "C"; 
     "D"; "E"; "F"
    ]
  let E = 
    [("A", "B", 100);
     ("A", "D", 115);
     ("B", "A", 80);
     ("B", "C", 20);
     ("B", "D", 12);
     ("C", "E", 29);
     ("D", "C", 7);
     ("E", "C", 29)
    ]
  //
  printfn "neighbors of A: %A" (neighbors "A" E)
  printfn "isEdge C to A?  %A" (isEdge "C" "A" E)
  printfn "isPath A to C?  %A" (isPath "A" "C" V E)
  printfn ""
  printfn "Don't forget to also run the unit tests..."
  printfn ""
  //
  0
