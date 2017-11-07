// AoG HW 2.2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <list>
#include <vector>

using namespace std;

class Graph
{
	int V;    // No. of vertices'

			  // Pointer to an array containing adjacency listsList
	list<int> *adj;

	// A function used by topologicalSort
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
	Graph(int V);   // Constructor

					// function to add an edge to graph
	void addEdge(int v, int w);

	// prints a Topological Sort of the complete graph
	void topologicalSort();
};

Graph::Graph(int V)
{
	int V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
	stack<int> &Stack)
{
	// Mark the current node as visited.
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	// Push current vertex to stack which stores result
	Stack.push(v);
}

// The function to do Topological Sort. It uses recursive 
// topologicalSortUtil()
void Graph::topologicalSort()
{
	stack<int> Stack;

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological
	// Sort starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	// Print contents of stack
	while (Stack.empty() == false)
	{
		cout << Stack.top() + 1 << " ";
		Stack.pop();
	}
}

int main()
{
	//creating variables to be used to find out if vertices in path are connected
	int nVertices = 0;
	int mEdges = 0;
	int start_vert = 0;
	int end_vert = 0;

	//enter number of vertices and edges first
	cin >> nVertices >> mEdges;
	Graph g(nVertices);
	//input all edges between two vertices
	for (int i = 1; i < mEdges + 1; i++)
	{
		cin >> start_vert >> end_vert;
		//inversion of the anticipated vertex list
		g.addEdge(start_vert - 1, end_vert - 1);
	} 

	g.topologicalSort();

    return 0;
}

