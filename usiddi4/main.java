//	  Assignment: Program 1, Mid Meeting 
//	  Author: Usman Siddiqui
//	  Class: CS 342, Fall 2016
//
//	  Author Code Number: 1325S
//
//
//    Read in information from city distance files.  Use this to do a DFS.
//    The graph is stored using adjacency lists.
// Vertices are inserted into adjacency lists in ascending order.
/* Running this program gives:
 
 AZ BD BN BY BS CO CN CH GM HU IL JU LN MA ME MY ML MW NS NY PY PS RO RE SF SO SE SI SY TO
 
 Vertex     Adjacency List
 ------     --------------
 
 0       13 19 22 23 24 29
 1       2 8 9 13 15 21 24 25 28
 2       1 5 7 8 9 10 11 12 13 28
 3       4 7 8 11 17 20 21 27
 4       3 14 20 21 22
 5       2 9 10 11 15 16 17 21 28
 6       8 9 13 14 15 16 18 20 21 23
 7       2 3 9 12 19 21 23 24 29
 8       1 2 3 6 13 15 17 21 23
 9       1 2 5 6 7 11 13 20 22 24 27
 10       2 5 12 13 15 16 21 25
 11       2 3 5 9 13 19 20 23 28
 12       2 7 10 18 19 20 22 28 29
 13       0 1 2 6 8 9 10 11 15 20 28
 14       4 6 20 21 24 27
 15       1 5 6 8 10 13 17 18 22 25
 16       5 6 10 19 24 27
 17       3 5 8 15 23
 18       6 12 15 19 23 26 27
 19       0 7 11 12 16 18 21 25 26
 20       3 4 6 9 11 12 13 14 21 25 26
 21       1 3 4 5 6 7 8 10 14 19 20 22 27 29
 22       0 4 9 12 15 21 25 26
 23       0 6 7 8 11 17 18 24
 24       0 1 7 9 14 16 23 27
 25       1 10 15 19 20 22 27 28
 26       18 19 20 22
 27       3 9 14 16 18 21 24 25 29
 28       1 2 5 11 12 13 25
 29       0 7 12 21 27
 
 Breadth First Search gives: 0 13 19 22 23 24 29 1 2 6 8 9 10 11 15 20 28 7 12 16 18 21 25 26 4 17 14 27 5 3
 
 */
package Program1;
import static java.lang.System.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class main {
	private static int MAX_VERTICES = 248;	// Max Vertices
	
	public static void displayAdjacencyLists(node graph[])  // Array of adjacency list heads
	{
	    node pTemp;
	    
	    System.out.println("\n   Vertex     Adjacency List \n   ------     -------------- \n");
	    
	    // Display adjacency lists for non-empty rows
	    for( int i=0; i<MAX_VERTICES; i++) {
	        if( graph[ i] != null) {
	            // Display vertex number
	            System.out.print("   "+i+"\t      ");
	            
	            // Display associated list
	            pTemp = graph[ i];
                pTemp = pTemp.getNext();//	First vertex is the head so skip over it
	            while( pTemp!=null) {
	                System.out.print(pTemp.getVertex()+ " ");
	                pTemp = pTemp.getNext();
	            }//end while( pTemp...
	            System.out.println();
	            
	        }//end if( graph[ i]...
	    }//end for( int i...
	    
        System.out.println();
	}//end displayAdjacencyLists(...)
	
	// Store a node into an adjacency list in ascending order.
	public static void insertIntoListInOrder(
	                           node pNewNode,    // New Node to be inserted in order into list
	                           node pHead)     // Head of the list, which may change
	{
	    node pTemp = pHead;
	    int newVertex = pNewNode.getVertex();
	    
	    // Check to see if list is empty
	    if (pHead == null)  {
	        // list is empty, so make this the first node
	        pHead = pNewNode;
	    }
	    else  {
	        // list is not empty
	        pTemp = pHead;
	        
	        // Iterate through list to find insertion location
	        while ( (pTemp.getNext() != null) && (newVertex > pTemp.getNext().getVertex()) )  {
	            pTemp = pTemp.getNext();        // advance to next node
	        }
	        
	        // See if number goes at front of list
	        if ( newVertex < pHead.getVertex())  {
	            // insert at front of list
	            pNewNode.setNext(pHead);
	            pHead = pNewNode;
	        }
	        else {
	            // Node goes in the middle or at the end of list
	            // Insert after node pointed to by pTemp
	            pNewNode.setNext(pTemp.getNext());   // Redundant assignment of NULL
	            //    if appending to end of list
	            pTemp.setNext(pNewNode);
	        }
	    } // end else
	}//end insertIntoListInOrder(...)

	//-----------------------------------------------------------------------------
	// Store vertex1 into the adjacency list for vertex2.
//	    The macro  INSERT_IN_ORDER  defined at the top of the program determines
	// whether vertices on each adjacency list are stored in LIFO order or in
	// ascending order.
	public static void storePairIntoAdjacencyLists(
	                                 node graph[],          // Array of adjacency list heads
	                                 int vertex1,           // First vertex of edge being added
	                                 int vertex2,           // Second vertex of edge being added
	                                 int distance,			// Distance between the vertices
	                                 int numberOfVertices)  // Total number of vertices in graph
	{
	    // Place vertex 1 in vertex 2's adjacency list
	    node pTemp = new node();
	    pTemp.setVertex(vertex1);		 // Store vertex number
	    pTemp.setNext(null);     		 // If this will be 1st node, ensure NULL termination
	    pTemp.setDistance(distance);	 // Store the distance between nodes
	    
	    // If graph[ vertex2] is NULL, this is a new vertex so increment count
	    if( graph[ vertex2] == null) {
	        numberOfVertices++;
	    }
	    
	    // Vertices on adjacency lists are stored in ascending order.
	    insertIntoListInOrder( pTemp, graph[ vertex2]);
	    
	}//end storePairIntoAdjacencyLists(...)


	//-----------------------------------------------------------------------------
	// Store vertex1 into the adjacency list for vertex2, and vertex2 into the
	// adjacency list for vertex1.
	public static void storeEdgeIntoGraph(
	                        node graph[],           // Array of adjacency list heads
	                        int vertex1,            // First vertex of edge being added
	                        int vertex2,            // Second vertex of edge being added
                            int distance,			// Distance between the vertices
	                        int numberOfVertices)   // Total number of vertices in graph
	{
	    // Store vertex 1 onto the adjacency list for vertex 2.
	    storePairIntoAdjacencyLists( graph, vertex1, vertex2, distance, numberOfVertices);
	    
	    // Store vertex 2 onto the adjacency list for vertex 1.
	    storePairIntoAdjacencyLists( graph, vertex2, vertex1, distance, numberOfVertices);
	    
	}//end storeEdgeIntoAdjacencyLists(...)


	//-----------------------------------------------------------------------------
	// Prompt for input, using it to create graph adjacency lists.
	public static void createAdjacencyLists( node graph[], int numberOfVertices)
	{
	    // Initialize all adjacency lists to NULL
	    for (int i = 0; i < MAX_VERTICES; i++) {
	        graph[i] = null;
	    }
	    
	    // Comment out this section and uncomment out the following section
	    // if you want to provide interactive user input.
	    //
	    // Manually add the pairs to create the graph:
	    //           1
	    //          / \
	    //         2   3
	    //        / \ / \
	    //       4   5   6
	    //        \ / \ /
	    //         7   8
	    //
	    
	}//end createAdjacencyLists(...)


	//-----------------------------------------------------------------------------
	// Display queue values from front to back.  Used for debugging.
//	      front -> ... -> back
	public static void displayQueue( node pFront)
	{
	    System.out.print("\nFrom front to back queue is:  ");
	    while( pFront != null) {
	        System.out.print(pFront.getVertex() + " ");
	        pFront = pFront.getNext();
	    }
	    System.out.println();
	}//end displayQueue( ...)


	//-----------------------------------------------------------------------------
	// Add node to back of queue.
	// Queue pointers point from front to back:   front -> ... -> back
	public static void addToBack( node pFront, node pBack, int input)
	{
	    // Get a new node and add the data
	    node pTemp = new node();
	    pTemp.setVertex(input);
	    pTemp.setNext(null);
	    
	    // See if this is the first node
	    if( pBack != null) {
	        // Append to back of queue
	        pBack.setNext(pTemp);
	    }
	    else {
	        // pBack is NULL, so this is the first node.  Adjust pFront as well.
	        pFront = pTemp;
	    }
	    
	    // Reset back pointer to point to new back of queue
	    pBack = pTemp;
	}//end addToBack(...)


	//-----------------------------------------------------------------------------
	// Remove an element from the front of the queue.
	// Queue pointers point from front to back:   front -> ... -> back
	public static int removeFromFront( node pFront, node pBack)
	{
	    node pTemp;             // keep track of node to be deleted
	    int returnValue = -1;        // keep track of return value
	    
	    if( pFront != null) {
	        returnValue = pFront.getVertex();
	        pTemp = pFront;  // keep track of node for deletion
	        pFront = pFront.getNext();
	    }
	    else {
	        System.out.println("   Sorry, can't remove from an empty queue. ");
	    }
	    
	    // If that was the last node and was just removed, also adjust the back pointer
	    if( pFront == null) {
	        pBack = null;
	    }
	    
	    return returnValue;
	}//end removeFromFront(...)


	//-----------------------------------------------------------------------------
	// Perform a breadth-first search (BFS) for the following graph:
//	           1
//	          / \
//	         2   3
//	        / \ / \
//	       4   5   6
//	        \ / \ /
//	         7   8
	public static void breadthFirstSearch(
	            int currentVertex,   // Current vertex being handled
	            node graph[],       // Adjacency lists representing the graph
	            int visited[])       // Elements set to 1 when vertex is visited
	{
	    // Queue pointers for breadth-first search
	    node pFront = null;  // elements are removed from front of queue
	    node pBack = null;   // elements are added to back of queue
	    node pTemp;
	    
	    // Add starting vertex to queue
	    addToBack( pFront, pBack, currentVertex);
	    // Mark it as visited
	    visited[ currentVertex] = 1;   // set visited value to true for this vertex
	    // displayQueue( pFront);   // For debugging
	    
	    // While there are elements on the queue (pFront != NULL)
	    while( pFront != null) {
	        // Retrieve the next queue element
	        currentVertex = removeFromFront( pFront, pBack);
	        
	        // Display it and mark it as visited.
	        System.out.print(currentVertex + " ");  // display vertex being visited
	        
	        // Add each of its unvisited children to the back of queue
	        for( pTemp=graph[ currentVertex]; pTemp!=null; pTemp = pTemp.getNext()) {
	            if( visited[ pTemp.getVertex()] == 0) {
	                addToBack( pFront, pBack, pTemp.getVertex());
	                visited[ pTemp.getVertex()] = 1;   // set visited value to true for this vertex
	            }
	        }//end for( pTemp...
	        // displayQueue( pFront);   // For debugging
	        
	    }//end while( pFront)
	    
	}//end breadthFirstSearch(...


	//-----------------------------------------------------------------------------
	// Read in the city names from one file and the list of distances between
	// pairs of cities from another file, storing these pairs into the adjacency
	// graph as we go.
	public static void readInContentFromFiles(
	            String cityNames[],            // Array of city names
	            node graph[],                  // Array of adjacency lists for graph
	            int numberOfVertices)          // Number of vertices in graph
	{
		int howManyCities = 0;
		
		try (BufferedReader br = new BufferedReader(new FileReader("CityNames.txt")))// Set up br to have the text file in it
		{

			String sCurrentLine;
			if((sCurrentLine = br.readLine()) != null)
				howManyCities = Integer.parseInt(sCurrentLine);
			if(howManyCities != MAX_VERTICES){
				System.out.println("Error change MAX_VERTICES");
				System.exit(0);
			}
			for (int i=0;(sCurrentLine = br.readLine()) != null;i++) {// read the line in the file
				cityNames[i] = sCurrentLine; // cityNames[i] is now the city name + state
			}

		} catch (IOException e) {// If it fails to read prints stack trace
			e.printStackTrace();
		}
		
		/* echo city initials
	    System.out.println();
	    for( int i=0; i<howManyCities; i++) {
	        System.out.print(cityNames[ i] + " ");
	    }
	    System.out.println();
	    */
	    
	    // Now read in the distance values

	    int howManyPairs = 0;
	    int fromCity, toCity, distance;
	    try (BufferedReader br = new BufferedReader(new FileReader("CityDistances.txt")))// Set up br to have the text file in it
		{

			String sCurrentLine;

			
			if((sCurrentLine = br.readLine()) != null)
				howManyPairs = Integer.parseInt(sCurrentLine);	    // First read the number of distance pairs from the first line
			while ((sCurrentLine = br.readLine()) != null) {// read the line in the file
				String[] tokens = sCurrentLine.split(" ");// Parse each line by spaces
			    // Now read the distance pairs and store in adjacency lists
				fromCity = Integer.parseInt(tokens[0]);
				toCity = Integer.parseInt(tokens[1]);
				distance = Integer.parseInt(tokens[tokens.length-1]);
		        storeEdgeIntoGraph( graph, fromCity-1, toCity-1, distance, numberOfVertices);

			}

		} catch (IOException e) {// If it fails to read prints stack trace
			e.printStackTrace();
		}
	    
	}//end readInContentFromFiles(...)
	
	
	// Implement Prim's algorithm.
	// The prims portion of code is modified from Steven Skiena's "Algorithm Design Manual", 2008
//	     http://www3.cs.stonvertexbrook.edu/~skiena/algorist/book/programs/prim.c
	//
	// This is a greedvertex algorithm that does the following:
//	    Select some starting point vertex s
//	    while( there are still non-tree vertices) {
//	       Select the edge with min weight between a tree and non-tree vertex
//	       Add the newly selected edge and vertex to the tree
	public static void primCreateMinSpanningTree(
	                               node graph[], 		  // Graph represented by adjacency lists
	                               int start, 			  // Starting node for building min spanning tree
	                               int parent[],   	      // Array of parent pointers, which will represent spanning tree
	                               int numberOfVertices,   // How many vertices are in tree
								   String cityNames[])		  // City names for outputting
	{
	    node pTemp;					// temporary graph node pointer
	    boolean[] isInTree = new boolean[MAX_VERTICES];	// Marks if vertex is in the tree
	    int[] distance = new int[MAX_VERTICES];		// Min distance found so far for each vertex
	    int currentVertex;				// current vertex to process
	    int adjacentVertex;				// Adjacent vertex
	    int weight;						// edge weight
	    int shortestNewNodeDistance;	// shortest distance of some new node from current node
	    
	    // Initialize all vertices as not being in the tree, having max distance and no parent.
	    for (int i=0; i<numberOfVertices; i++) {
	        isInTree[i] = false;
	        distance[i] = Integer.MAX_VALUE;
	        parent[i] = -1;
	    }
	    
	    // Set values for starting node
	    distance[start] = 0;
	    currentVertex = start;
	    
	    // main loop, continued until all vertices are handled
	    while (isInTree[ currentVertex] == false) {
	        isInTree[ currentVertex] = true;	// Include current vertex into tree
	        
	        // Examine in turn each edge incident to the current vertex
	        pTemp = graph[ currentVertex];	     // Get first edge
	        while (pTemp.getNext() != null) {
	            adjacentVertex = pTemp.getNext().getVertex();  // Get vertex on othe end of this edge
	            weight = pTemp.getNext().getDistance();			 // Get weight of this edge
	            // If this is a newly reachable vertex
	            /*
	            //  These next few lines are the original Prim's algorithm code
	            if ((distance[ adjacentVertex] > weight) && (isInTree[ adjacentVertex] == false)) {
	                // Store new lower-cost distance and spanning tree connection point
	                distance[ adjacentVertex] = weight;
	                parent[ adjacentVertex] = currentVertex;
	            }
	            */
	            
	            // The lines below are modified from the Prim's version (see above) to
	            // implement length from the start, not just local length.
	            if (distance[ adjacentVertex] > (distance[currentVertex] + weight) ) {
	                // Store new lower-cost distance and spanning tree connection point
	                distance[ adjacentVertex] = distance[currentVertex] + weight;
	                parent[ adjacentVertex] = currentVertex;
	            }
	            
	            pTemp = pTemp.getNext();  // advance to next edge incident on currentVertex
	        }
	        
	        // Find next vertex to be processed.  It should be the closest one not already in tree.
	        currentVertex = 1;
	        shortestNewNodeDistance = Integer.MAX_VALUE;		  // Initialize to some large number
	        // Examine each vertex in graph
	        for (int i=0; i<numberOfVertices; i++) {
	            if ((isInTree[i] == false) && (shortestNewNodeDistance > distance[i])) {
	                // This ith vertex is not yet in tree and is closest so far
	                shortestNewNodeDistance = distance[i];  // set new shortest distance
	                currentVertex = i;                      // set new closest vertex
	            }
	        }//end for( int i...
	        
	    }//end while( isInTre...
	    
	    // Display distance from start to each other node
	    System.out.println("Distance from " + start + " or "+ cityNames[start]+ " to each other node is:");
	    for( int i=0; i<numberOfVertices; i++) {
	        System.out.println(cityNames[i] + ":\t\t\t" + +distance[i]);
	    }
	    System.out.println();
	}//end primCreateMinSpanningTree(...)
	
	
	public static void primCreateMinSpanningTreeRevised(
			node graph[], 		  	// Graph represented by adjacency lists
			int start, 				// Starting node for building min spanning tree
			int parent[],   	  	// Array of parent pointers, which will represent spanning tree
			int numberOfVertices, 	// How many vertices are in tree
			int distance[])		   	// distance to be manipulated
	{
		node pTemp;					// temporary graph node pointer
		boolean[] isInTree = new boolean[MAX_VERTICES];	// Marks if vertex is in the tree
		int currentVertex;				// current vertex to process
		int adjacentVertex;				// Adjacent vertex
		int weight;						// edge weight
		int shortestNewNodeDistance;	// shortest distance of some new node from current node

		// Initialize all vertices as not being in the tree, having max distance and no parent.
		for (int i=0; i<numberOfVertices; i++) {
			isInTree[i] = false;
			distance[i] = Integer.MAX_VALUE;
			parent[i] = -1;
		}

		// Set values for starting node
		distance[start] = 0;
		currentVertex = start;

		// main loop, continued until all vertices are handled
		while (isInTree[ currentVertex] == false) {
			isInTree[ currentVertex] = true;	// Include current vertex into tree

			// Examine in turn each edge incident to the current vertex
			pTemp = graph[ currentVertex];	     // Get first edge
			while (pTemp.getNext() != null) {
				adjacentVertex = pTemp.getNext().getVertex();  // Get vertex on othe end of this edge
				weight = pTemp.getNext().getDistance();			 // Get weight of this edge
				// If this is a newly reachable vertex
				/*
				//  These next few lines are the original Prim's algorithm code
				if ((distance[ adjacentVertex] > weight) && (isInTree[ adjacentVertex] == false)) {
				// Store new lower-cost distance and spanning tree connection point
				distance[ adjacentVertex] = weight;
				parent[ adjacentVertex] = currentVertex;
				}
				 */

				// The lines below are modified from the Prim's version (see above) to
				// implement length from the start, not just local length.
				if (distance[ adjacentVertex] > (distance[currentVertex] + weight) ) {
					// Store new lower-cost distance and spanning tree connection point
					distance[ adjacentVertex] = distance[currentVertex] + weight;
					parent[ adjacentVertex] = currentVertex;
				}

				pTemp = pTemp.getNext();  // advance to next edge incident on currentVertex
			}

			// Find next vertex to be processed.  It should be the closest one not already in tree.
			currentVertex = 1;
			shortestNewNodeDistance = Integer.MAX_VALUE;		  // Initialize to some large number
			// Examine each vertex in graph
			for (int i=0; i<numberOfVertices; i++) {
				if ((isInTree[i] == false) && (shortestNewNodeDistance > distance[i])) {
					// This ith vertex is not yet in tree and is closest so far
					shortestNewNodeDistance = distance[i];  // set new shortest distance
					currentVertex = i;                      // set new closest vertex
				}
			}//end for( int i...

}//end while( isInTre...

}//end primCreateMinSpanningTreeRevised(...)
	// Makes an array for prim?
	public static void listMaker(node graph[], int array[], int start){
		node pTemp = graph[start];
		
		pTemp = pTemp.getNext();
		for(int i=0; pTemp!=null;i++,pTemp=pTemp.getNext())
			array[i] = pTemp.getVertex();
			
	}
	//Used to get participants from the file Participants.txt
	public static int[] recordParticipants(){
		int participants = 0;
		
		try (BufferedReader br = new BufferedReader(new FileReader("Participants.txt")))// Set up br to have the text file in it
		{

			String sCurrentLine;
			if((sCurrentLine = br.readLine()) != null)
				participants = Integer.parseInt(sCurrentLine);
			int[] participantCities = new int[participants];
			for (int i=0;(sCurrentLine = br.readLine()) != null;i++) {// read the line in the file
				String[] tokens = sCurrentLine.split(" ");// Parse each line by spaces
				participantCities[i] = Integer.parseInt(tokens[1])-1; 
				// Records the city, throws out the name for each participant
			}
			return participantCities;
		} catch (IOException e) {// If it fails to read prints stack trace
			e.printStackTrace();
			return null;
		}
	}
	
	public static void getMid(node graph[], int participants[], int parent[], String cityNames[]){
		int[][] distance = new int[participants.length][MAX_VERTICES];
		
		
		// Idea that does not work, wanted to skip repeats and just multiply instead of add
		//int multiplier;
		//for(int i=0;i<participants.length;i++){
		//	System.out.println(participants[i]);
		//}
		//for(int i=0;i<participants.length;i++){
		//	multiplier = 1;
		//	for(int j=0;j<i;j++){
		//		if(participants[i] == participants[j] && participants[i] != -1){
		//			multiplier++;
		//			participants[j] = -1;
		//		}
		//	}
		//	if(participants[i] != -1)
		//		primCreateMinSpanningTreeRevised(graph, participants[i], parent, MAX_VERTICES,distance[i]);
		//	for(int k=0;k<MAX_VERTICES && multiplier > 1;k++)
		//			distance[i][k] *= multiplier;
		//	
		//}
		int[] result = new int[MAX_VERTICES];// Stores the total distances
		for(int i=0;i<participants.length;i++){
		//	if(participants[i] != -1)	legacy code? :o
			primCreateMinSpanningTreeRevised(graph, participants[i], parent, MAX_VERTICES,distance[i]);// Get distance
			for(int j=0;j<MAX_VERTICES;j++)
				result[j] += distance[i][j];// Compile total distances
		}
		// Set up to find smallest distance
		double smallest = Integer.MAX_VALUE;
		int location = -1;
		// Find smallest distance
		for(int i=0;i<MAX_VERTICES;i++)
			if(smallest > result[i]){
				smallest = result[i];
				location = i;
			}
		// Output city name and the smallest average distance (found smallest total distance then get average by smallest/participants.length)
		System.out.println("The city with the smallest average is: "+ cityNames[location]
				+ " \nWith average distance of: "+ smallest/participants.length);
	}
	
	public static void main(String args[]){
		
	    node[] graph = new node[MAX_VERTICES];   // The graph, as adjacency lists
	    int numberOfVertices = 0;	   // How many vertices currently in the graph
	    int[] parent = new int[MAX_VERTICES];    // Used for Prim
	    
	    String[] cityNames = new String[ MAX_VERTICES];
	    
	    // Initialize all adjacency lists to new nodes
	    for (int i = 0; i < MAX_VERTICES; i++) {
	        graph[i] = new node();
	    }
	    	    
	    // Read in city names and distances from input files.
	    // Store distances into adjacency lists as they are read in.
	    readInContentFromFiles( cityNames, graph, numberOfVertices);
	    numberOfVertices = MAX_VERTICES;
	    
	    
	    // Display Adjacency lists.
	    displayAdjacencyLists( graph);
	    listMaker(graph,parent,57);
	    primCreateMinSpanningTree(graph, 57, parent, numberOfVertices, cityNames);
	    // Set up and record participants
	    int[] participants;
	    participants = recordParticipants();
	    // Find midpoint using this function
	    getMid(graph, participants, parent, cityNames);
	    System.out.println("\n\n");
	    // Print info
	    System.out.println("\tAuthor: Usman Siddiqui\n\tClass: CS 342, Fall 2016\n\tAuthor Code Number: 1325S");
	}// end main()
	
	
}
