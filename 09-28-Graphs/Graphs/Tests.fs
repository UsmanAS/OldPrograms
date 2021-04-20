#light

module UnitTests

open NUnit.Framework
open Functions

[<TestFixture>]
type UnitTests() = 
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
  // neighbors:
  //
  [<Test>]
  member this.neighbors_Test1() = 
    let N = neighbors "A" E
    Assert.IsTrue(List.sort N = ["B";"D"])

  [<Test>]
  member this.neighbors_Test2() = 
    Assert.IsTrue((neighbors "F" E) = [])

  [<Test>]
  member this.neighbors_Test3() = 
    let N = neighbors "B" E
    Assert.IsTrue(List.sort N = ["A";"C";"D"])

  [<Test>]
  member this.neighbors_Test4() = 
    Assert.IsTrue((neighbors "C" E) = ["E"])

  //
  // isEdge:
  //
  [<Test>]
  member this.isEdge_Test1() = 
    Assert.IsTrue(isEdge "A" "B" E)

  [<Test>]
  member this.isEdge_Test2() = 
    Assert.IsTrue(isEdge "B" "A" E)

  [<Test>]
  member this.isEdge_Test3() = 
    Assert.IsTrue(isEdge "C" "E" E)

  [<Test>]
  member this.isEdge_Test4() = 
    Assert.IsFalse(isEdge "D" "E" E)

  [<Test>]
  member this.isEdge_Test5() = 
    Assert.IsFalse(isEdge "D" "D" E)

  [<Test>]
  member this.isEdge_Test6() = 
    Assert.IsFalse(isEdge "F" "E" E)

  [<Test>]
  member this.isEdge_Test7() = 
    Assert.IsFalse(isEdge "F" "F" E)
    
  //
  // isPath:
  //
  [<Test>]
  member this.isPath_Test1() = 
    Assert.IsTrue(isPath "A" "B" V E)

  [<Test>]
  member this.isPath_Test2() = 
    Assert.IsTrue(isPath "D" "E" V E)

  [<Test>]
  member this.isPath_Test3() = 
    Assert.IsTrue(isPath "A" "C" V E)

//  [<Test>]
//  member this.isPath_Test4() = 
//    Assert.IsTrue(isPath "A" "E" V E)
//
//  [<Test>]
//  member this.isPath_Test5() = 
//    Assert.IsFalse(isPath "B" "F" V E)
//
//  [<Test>]
//  member this.isPath_Test6() = 
//    Assert.IsFalse(isPath "F" "F" V E)
