// AoG HW 4.2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

struct Edge
{
	int source;
	int dest;
	int w;
};

class Graph
{
private:
	int nV;
	vector <Edge> edges;
public:

	Graph(int V)
	{
		nV = V;
	}

	void addEdge(int s, int d, int w)
	{
		Edge e;
		e.source = s;
		e.dest = d;
		e.w = w;

		edges.push_back(e);
	}

	bool IsNegCycle()
	{
		int u = 1;
		vector <int> d(nV + 1, 1000000);
		d[u] = 0;
		int v = 0;
		int dist = 0;
		for (int i = 1; i < nV - 1; i++)
		{
			for (int j = 0; j < edges.size(); j++)
			{
				u = edges[j].source;
				v = edges[j].dest;
				dist = edges[j].w;
				if (d[v] > d[u] + dist)
				{
					d[v] = d[u] + dist;
				}
			}
		}

		for (int i = 0; i < edges.size(); i++)
		{
			u = edges[i].source;
			v = edges[i].dest;
			dist = edges[i].w;
			if (d[v] > d[u] + dist)
			{
				return 1;
			}
		}
		return 0;
	}
};

int main_with_large_stack_space()
{
	//creating variables to be used to find out if vertices in path are connected
	int nVertices = 0;
	int mEdges = 0;
	int start_vert = 0;
	int end_vert = 0;
	int first_vert = 0;
	int last_vert = 0;
	int dist = 0;
	//enter number of vertices and edges first
	std::cin >> nVertices >> mEdges;
	Graph g(nVertices + 1);
	//input all edges between two vertices
	for (int i = 0; i < mEdges; i++)
	{
		std::cin >> start_vert >> end_vert >> dist;
		g.addEdge(start_vert, end_vert, dist);
	}
	//enter two vertices as starting and end vertices of graph
	cout << g.IsNegCycle() << endl;
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}

#endif
	return main_with_large_stack_space();
}