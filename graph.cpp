#pragma once
/*graph.cpp*/

#include <iostream>
#include <set>
#include "graph.h"
#include <queue>
using namespace std;


//
// Constructor:
//
Graph::Graph(int N)
{
	this->NumVertices = 0;
	this->NumEdges = 0;
	this->Capacity = N;

	this->Vertices = new Edge*[N];
	this->Names = new string[N];

}


//
// Destructor:
//
Graph::~Graph()
{
	//
	// Future work:
	//
}


//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
{
	//
	// if the graph is "full", i.e. cannot hold more vertices,
	// then return false:
	//
	// TODO #1
	//
	if (this->Capacity == this->NumVertices) {
		return false;
	}

	//
	// if the vertex name already exists in the graph,
	// then return false.  To determine, perform a linear
	// search of the Names array; note that in C++ you
	// compare strings using ==, no strcmp needed:
	//
	// TODO #2
	//
	int a;
	for (a = 0; a < this->Capacity; a++) {
		if (this->Names[a] == v) {
			return false;
		}
	}

	//
	// there's room to add another vertex, so grab next index
	// and initialize that linked-list to empty, and store
	// vertex's name:
	//
	int i = this->NumVertices;

	this->Vertices[i] = nullptr;  // head of LL: null
	this->Names[i] = v;           // copy vertex string:

	this->NumVertices++;
	return true;
}

//
// AddEdge:
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
	// 
	// First, lookup src vertex in Names array and obtain index S; if
	// not found, return false:
	//
	int a;
	for (a = 0; a < this->Capacity; a++) {
		if (src == this->Names[a]) {
			break;
		}
	}

	if (a == this->Capacity) {
		return false;
	}


	//
	// Second, lookup dest vertex in Names array and obtain index D, if
	// not found, return false:
	//
	int b;
	for (b = 0; b < this->Capacity; b++) {
		if (dest == this->Names[b]) {
			break;
		}
	}

	if (b == this->Capacity) {
		return false;
	}
	//
	// Now add an edge (S,D,weight) to the front of S's linked-list.
	// You'll need to allocate a new edge using new, store S, D and
	// weight, and then insert at head of S's linked-list in the
	// Vertices array:
	//

	Edge *e = new Edge();
	e->Src = a;
	e->Dest = b;
	e->Weight = weight;

	//Creating helper pointers and setting them to NULL
	Edge *previous = NULL;
	Edge *Current = NULL;

	//Setting current to "Head"
	Current = this->Vertices[a];
	while (Current) {
		if (Current->Dest == e->Dest)
		{
			//if (Current->Weight > e->Weight)
			//{
			//	//Break out of loop
			//	break;
			//}
			Current->Weight++;
			return false;

		}
		//If the Curr destination is greater than e Dest(node we insert) 
		else if (Current->Dest > e->Dest)
		{
			//Then Break out of loop
			break;
		}

		//Advancing the search
		previous = Current;
		Current = Current->Next;
	}

	//If Prev is NULL then
	if (previous == NULL)
	{
		//Link it to the head
		e->Next = this->Vertices[a];
		this->Vertices[a] = e;
	}

	//otherwise
	else
	{
		//Link it back together
		e->Next = previous->Next;
		previous->Next = e;
	}

	// ..
	//
	// increment the # of edges and return true:
	//
	this->NumEdges++;

	return true;
}


//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
	cout << ">>Graph: " << title << endl;
	cout << "  # of vertices: " << this->NumVertices << endl;
	cout << "  # of edges:    " << this->NumEdges << endl;
	cout << "  Capacity:      " << this->Capacity << endl;

	cout << "  Vertices:" << endl;

	for (int v = 0; v < this->NumVertices; ++v)
	{
		cout << "    " << v << " (" << this->Names[v] << "): ";

		Edge *edge = this->Vertices[v];
		while (edge != nullptr)
		{
			cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";

			edge = edge->Next;
			if (edge != nullptr)
				cout << ", ";
		}

		cout << endl;
	}
}


//
// GetVertices:
//
// Returns a set containing all vertices in the graph.
//                    
set<string> Graph::GetVertices()
{
	set<string>  vertices;

	int a =                            ;

	while (a > 0)
	{
		a--;
		vertices.insert(this->Names[a]);

	}
	//cout << "*****  " << this->Names[a] << endl;
	return vertices;
}


//
// GetNeighbors:
//
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v, int &count, int &b)
{
	set<string>  neighbors;

	int a = 0;
	a = NumVertices;
	while (a > 0) {
		a--;
		if (this->Names[a] == v) { //WHen match found
			break; //break
		}
	}

	//Creating a temporary variable
	Edge *temporary = this->Vertices[a];
	while (NULL != temporary) {      //While loop

		count++;
		b = b + temporary->Weight;
		 //Inserting the neighbors
		neighbors.insert(this->Names[temporary->Dest]);

		//advancing the pointer
		temporary = temporary->Next;
	}

	return neighbors;
}


//
// GetEdgeWeights:
//
// Returns a vector containing all the weights for edges 
// from src to dest.  The weights are in ascending order,
// and may contain duplicates (since it is legal for there
// to be 2 different edges from src to dest with the same
// weight).  If src or dest do not exist in the graph, the
// returned vector is empty.
//
vector<int> Graph::GetEdgeWeights(string src, string dest)
{
	vector<int> weights;

	int a, b = 0;
	a = NumVertices;
	while (a > 0) {
		a--;
		if (this->Names[a] == src) {
			break;
		}
	}

	Edge *temporary = this->Vertices[a];

	while (NULL != temporary) {

		if (this->Names[temporary->Dest] == dest) {
			//If name match, then push onto 
			weights.push_back(temporary->Weight);
		}

		temporary = temporary->Next;
	}

	return weights;
}

//
// BFS:
//
// Performs a breadth-first search starting from vertex v, returning
// a vector that denotes the order in vertices were visited.  If v
// does not exist in the graph, an empty vector is returned.
//
// NOTE that a vertex will appear at most once in the returned vector,
// since once a vertex is visited, it is never visited again.
//

int Graph::FindVertexByName(string v) {

	int a = 0;

	while (this->Names[a] != "\0") {
		if (this->Names[a] == v) {
			break;
		}
		a++;
	}

	return a;
}

vector<int> Graph::iNeighbors(int v) {
	vector<int> iNeighbors;
	//Creating temp pointer
	Edge *temporary = this->Vertices[v];
	//While temp is not NULL(traversing)
	while (temporary != nullptr) {
		//pushing all the neighbors on
		iNeighbors.push_back(temporary->Dest);
		//Advacning the pointer
		temporary = temporary->Next;
	}
	return iNeighbors;
}

//BFS implementation from Hummel's SUDO code that
//Was given to us in class
vector<string> Graph::BFS(string v, int &count)
{
	vector<string>  visited;
	queue<int>      frontierQueue;
	set<int>        discoveredSet;

	int start = FindVertexByName(v);
	if (start < 0) {
		return visited;
	}
	frontierQueue.push(start);
	discoveredSet.insert(start);

	while (!frontierQueue.empty()) {
		int currentV = frontierQueue.front();
		frontierQueue.pop();
		visited.push_back(this->Names[currentV]);
		vector<int> V = iNeighbors(currentV);

		for (int adjv : V) {

			if (discoveredSet.find(adjv) == discoveredSet.end()) {
				frontierQueue.push(adjv);
				discoveredSet.insert(adjv);
				count++;
			}
		}
	}
	//
	// TODO:
	//
	return visited;
}

//Returns the number of verticies
int Graph::GetNumVertices() {
	return this->NumVertices;
}

//Returns the num of edges
int Graph::GetNumEdges() {
	return this->NumEdges;
}

//Gets the number of trips
// Very similar to my GetEdgeWeights function
//Except it reutrns the weight.
int Graph::NumTrips(string src, string dest) {

	//Declaring variables
	int a, b = 0;
	//setting a to number of verticies
	a = NumVertices;

	//Doing while loop to go through them all
	while (a > 0) {
		a--;
		if (this->Names[a] == src) { //If they match
			break; //then break
		}
	}

	//Create a temp Edge
	Edge *temporary = this->Vertices[a];

	//While null is not equal to temp
	while (NULL != temporary) {

		if (this->Names[temporary->Dest] == dest) {
			//If they match, return the weight that is associated with it 
			return temporary->Weight;
		}
		//Advancing
		temporary = temporary->Next;
	}

	//if not found return this
	return 0;
}

