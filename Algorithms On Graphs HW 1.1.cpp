// Algorithms On Graphs HW 1.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <vector>

//function to find to see if two points on a graph are connected
bool Explore(std::vector < std::stack <int> > vertex_list, int start, int end)
{
	int current_vertex = start;
	//create list of ancestor vertices to return to in case some of child vertices have been completely explored
	std::stack <int> ancestors;
	ancestors.push(start);
	while (!ancestors.empty())
	{
		//look in vertex list to see if end product can be found in chain 
		if (!vertex_list[start].empty())
		{
			current_vertex = vertex_list[start].top();
			vertex_list[start].pop();
			start = current_vertex;
			ancestors.push(start);
		}
		//once all edges connected to a vertex are cleared up, look into its ancestor's edges
		else
		{
			while (vertex_list[ancestors.top()].empty())
			{
				ancestors.pop();
				if (ancestors.empty())
				{
					return 0;
				}
			}

			start = ancestors.top();
		}
		//if a connection is found, return 1
		if (start == end)
			return 1;
	}
	//return 0 elsewise
	return 0;
}

int main()
{
	//creating variables to be used to find out if vertices in path are connected
	int nVertices = 0;
	int mEdges = 0;
	int start_vert = 0;
	int end_vert = 0;
	int first_vert = 0;
	int last_vert = 0;
	//saving vertices as vector of stack to create list of all vertices and their immediate neighbors
	std::vector < std::stack <int> > vertices;
	//enter number of vertices and edges first
	std::cin >> nVertices >> mEdges;
	//resize array to fit number of vertices
	vertices.resize(nVertices + 1);
	//input all edges between two vertices
	for (int i = 1; i < mEdges + 1; i++)
	{
		std::cin >> start_vert >> end_vert;

		vertices[start_vert].push(end_vert);
		vertices[end_vert].push(start_vert);
	}
	//enter two vertices as starting and end vertices of graph
	std::cin >> first_vert >> last_vert;
	//determine if the end vertex is reachable from the starting point
	std::cout << Explore(vertices, first_vert, last_vert) << std::endl;
    return 0;
}

