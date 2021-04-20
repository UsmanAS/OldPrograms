package Program1;

public class node {//	node needed for each vertex with distance and next node
	int vertex;
	int distance;
	node next;
	
	
	public node(){
		vertex = 0;
		next = null;
	}
	

	
	public node[] node(int n){
		node[] array = new node[n];
		for(int i = 0; i<n; i++)
			array[i] = new node();
		return array;
	}
	
	public node getNext(){// return next node
		return next;
	}
	
	public int getVertex(){// return the vertex
		return vertex;
	}
	
	public int getDistance(){//	return the distance to the next node
		return distance;
	}
	
	public void setNext(node tNext){// set next node
		next = tNext;
	}
	
	public void setVertex(int tVertex){// set vertex
		vertex = tVertex;
	}
	
	public void setDistance(int tDistance){//	set the distance
		distance = tDistance;
	}
}
