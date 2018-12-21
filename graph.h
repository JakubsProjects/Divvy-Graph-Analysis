#pragma once
/*graph.h*/

#pragma once

#include <string>
#include <vector>

using namespace std;

class Graph
{
private:
	class Edge
	{
	public:
		int   Src, Dest, Weight;
		Edge *Next;
	};

	Edge  **Vertices;
	string *Names;
	int     NumVertices;
	int     NumEdges;
	int     Capacity;

public:
	Graph(int N);
	~Graph();

	bool AddVertex(string v);
	bool AddEdge(string src, string dest, int weight);

	int NumTrips(string src, string dest);
	int GetNumVertices();
	int GetNumEdges();
	vector<int> iNeighbors(int v);
	int FindVertexByName(string v);
	vector<string> BFS(string v, int &count);
	set<string> GetVertices();
	set<string> GetNeighbors(string v, int &count, int &b);
	vector<int> GetEdgeWeights(string src, string dest);
	void PrintGraph(string title);
	
};
#pragma once
