// AoG HW 3.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
	vector <vector <int> > vertices;
	int numvert;
public:
	Graph(int v)
	{
		numvert = v;
		vertices.resize(numvert);
	}
	void addedge(int v, int w)
	{
		vertices[v].push_back(w);
	}
	//finding distances between 2 points
	int distance(int u, int v)
	{
		vector <int> distances(numvert + 1, -1);
		vector <int> prev(numvert + 1);
		queue <int> Q;
		distances[u] = 0;
		Q.push(u);
		int lookinto = u;
		while (!Q.empty())
		{
			//vertex to look into
			lookinto = Q.front();
			Q.pop();
			for (int i = 0; i < vertices[lookinto].size(); i++)
			{
				if (distances[vertices[lookinto][i]] == -1)
				{
					//filling in the previous vertex
					prev[ vertices[lookinto][i] ] = lookinto;
					//distance output between vertices
					distances[ vertices[lookinto][i] ] = distances[lookinto] + 1;
					if (vertices[lookinto][i] == v)
					{
						return distances[ vertices[lookinto][i] ];
					}
					Q.push(vertices[lookinto][i]);
				}

			}
		}

		return -1;
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
	//enter number of vertices and edges first
	std::cin >> nVertices >> mEdges;
	Graph g(nVertices + 1);
	//input all edges between two vertices
	for (int i = 0; i < mEdges; i++)
	{
		std::cin >> start_vert >> end_vert;
		g.addedge(start_vert, end_vert);
		g.addedge(end_vert, start_vert);
	}
	//enter two vertices as starting and end vertices of graph
	std::cin >> first_vert >> last_vert;
	cout << g.distance(first_vert, last_vert) << endl;

    return 0;
}

