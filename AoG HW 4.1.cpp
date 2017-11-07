// AoG HW 4.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
	vector <vector <int> > vertices;
	vector <vector <int> > distances;
	int numvert;
public:
	Graph(int v)
	{
		numvert = v;
		vertices.resize(numvert);
		distances.resize(numvert);
	}
	void addedge(int v, int w, int l)
	{
		vertices[v].push_back(w);
		distances[v].push_back(l);
	}
	//finding distances between 2 points
	int distance(int u, int v)
	{
		vector <int> d(numvert + 1, -1);
		vector <int> prev(numvert + 1);
		queue <int> Q;
		d[u] = 0;
		Q.push(u);
		int lookinto = u;
		while (!Q.empty())
		{
			//vertex to look into
			lookinto = Q.front();
			Q.pop();
			for (int i = 0; i < vertices[lookinto].size(); i++)
			{
				if (d[vertices[lookinto][i]] == -1)
				{
					//filling in the previous vertex
					prev[vertices[lookinto][i]] = lookinto;
					//distance output between vertices
					d[vertices[lookinto][i]] = d[lookinto] + 1;
					if (vertices[lookinto][i] == v)
					{
						return d[vertices[lookinto][i]];
					}
					Q.push(vertices[lookinto][i]);
				}

			}
		}
		return -1;
	}

	int djikstdistance(int u, int v)
	{
		vector <int> d(numvert + 1, 2147483647);
		vector <int> prev(numvert + 1);
		d[u] = 0;
		queue <int> Q;
		Q.push(u);
		int lookinto = u;
		while (!Q.empty())
		{
			lookinto = Q.front();
			Q.pop();
			for (int i = 0; i < vertices[lookinto].size(); i++)
			{
				if (d[vertices[lookinto][i]] > d[lookinto] + distances[lookinto][i])
				{
					//filling in the previous vertex
					prev[vertices[lookinto][i]] = lookinto;
					//distance output between vertices
					d[vertices[lookinto][i]] = d[lookinto] + distances[lookinto][i];
					Q.push(vertices[lookinto][i]);
				}
			}
		}

		if (d[v] == 2147483647)
		{
			return -1;
		}

		return d[v];
	}
};


int main()
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
		g.addedge(start_vert, end_vert, dist);
	}
	//enter two vertices as starting and end vertices of graph
	std::cin >> first_vert >> last_vert;
	cout << g.djikstdistance(first_vert, last_vert) << endl;
    return 0;
}

