// AoG HW 5.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
//edges between 2 x,y co-ordinates
struct Edge
{
	pair <double, double> source;
	pair <double, double> dest;
	double weight;
};
//discrete set class
class Set
{
private:
	int length;
public:
	vector < pair <double, double> > vertices;
	Set()
	{
		length = 0;
	}
	//add element to set
	void push(double x, double y)
	{
		pair <double, double> p = make_pair(x, y);
		if (!vertices.empty())
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices[i] == p)
					return;
			}
		}
		length++;
		vertices.push_back(p);
	}
	//size of set
	int size()
	{
		return length;
	}
	//true or false if an item is in list
	bool find(pair <double, double> p)
	{
		if (!vertices.empty())
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices[i] == p)
					return true;
			}
		}
		return false;
	}
	//union two sets
	Set Union(Set B)
	{
		Set AorB;
		for (int i = 0; i < vertices.size(); i++)
		{
			AorB.push(vertices[i].first, vertices[i].second);
		}
		
		for (int i = 0; i < B.size(); i++)
		{
			if (!find(B.vertices[i]))
			{
				AorB.push(B.vertices[i].first, B.vertices[i].second);
			}
		}
		return AorB;
	}
	//intersection between two sets
	Set Intersect(Set B)
	{
		Set AandB;
		for (int i = 0; i < B.size(); i++)
		{
			if (find(B.vertices[i]))
			{
				AandB.push(B.vertices[i].first, B.vertices[i].second);
			}
		}
		return AandB;
	}
};
//nodes for edges in a BST
struct Node
{
	Edge e;
	int left;
	int right;
};
//Binary Search Tree
class BST
{
private:
	int length;
public:
	vector <Node> leafs;
	//pair of vertices with the edge connecting them and the index they are located in the leaf array
	vector <pair <Edge, int> > ord_edges;
	BST()
	{
		length = 0;
	}
	//add leaf to tree
	void push(Edge E)
	{
		//initialize a node
		Node N;
		N.e = E;
		N.left = -1;
		N.right = -1;
		leafs.push_back(N);
		length++;
		//if the BST is empty
		if (length == 1)
		{
			return;
		}
		int i = 0;
		while (i != -1)
		{
			//if the weight of the leaf is less than the weight of the new edge, 
			if (leafs[i].e.weight < E.weight)
			{
				//if the leaf has no right part, add it to that part
				if (leafs[i].right == -1)
				{
					leafs[i].right = length - 1;
					return;
				}
				//if it does, compare it to its right leaf
				else
				{
					i = leafs[i].right;
				}
			}
			//if the weight of the new edge is less than the weight of the leaf,
			if (leafs[i].e.weight >= E.weight)
			{
				//if the leaf has no left part, add it to that part
				if (leafs[i].left == -1)
				{
					leafs[i].left = length - 1;
					return;
				}
				//if it does, compare it to its left leaf
				else
				{
					i = leafs[i].left;
				}
			}
		}

	}
	//find position of edge in tree
	int find(Edge E)
	{
		int position = 0;
		while (E.weight != leafs[position].e.weight && position != -1)
		{
			if (E.weight > leafs[position].e.weight)
			{
				position = leafs[position].right;
			}
			else
			{
				position = leafs[position].left;
			}
		}
		return position;
	}
	//order a binary tree
	void in_order(int i)
	{
		if (leafs[i].left == -1 && leafs[i].right == -1)
		{
			ord_edges.push_back( make_pair(leafs[i].e, i) );
			return;
		}
		if (leafs[i].left != -1)
		{
			in_order(leafs[i].left);
		}
		ord_edges.push_back(make_pair(leafs[i].e, i));
		if (leafs[i].right != -1)
		{
			in_order(leafs[i].right);
		}
	}
	//output ordered array
	vector < pair <Edge, int> > ordered()
	{
		return ord_edges;
	}
	//output length
	int size()
	{
		return length;
	}
};
//Graph class
class Graph
{
private:
	int nV;
public:
	BST edges;
	vector < pair <int, int> > vertpairs;
	vector < pair <double, double> > vertices;
	vector <Set> vertgroups;
	Graph(int V)
	{
		nV = V;
	}
	//add vertex to graph
	void addvert(double x, double y)
	{
		pair <double, double> vertex;
		vertex.first = x;
		vertex.second = y;
		vertices.push_back(vertex);
		Set newvert;
		newvert.push(vertex.first, vertex.second);
		vertgroups.push_back(newvert);
	}
	//generate all possible edges in graph (total of number of vertices squared)
	void MakeEdges()
	{
		//adds edges in starting from 0th vertex to the 1st vertex, then 0th to 2nd, and so on
		for (int i = 0; i < nV; i++)
		{
			for (int j = i + 1; j < nV; j++)
			{
				//creating sources and destinations for each edge
				pair <double, double> s = vertices[i];
				pair <double, double> d = vertices[j];
				Edge e;
				e.source = s;
				e.dest = d;
				//distance calculation
				e.weight = sqrt((d.first - s.first) * (d.first - s.first) + (d.second - s.second) * (d.second - s.second));
				edges.push(e);
				//array to remember the pairs of vertices between edges
				vertpairs.push_back(make_pair(i, j));
			}
		}
	}
	//Kruskal algorithm
	double KruskalDist()
	{
		//order edges from smallest to largest
		edges.in_order(0);
		vector< pair <Edge, int> > ordered = edges.ordered();
		double dist = 0;
		//for each of the smallest edges, make sure that the edge provides at least 1 new vertex each time
		//then from there, add those vertices into a set and then add the distance between these vertices to
		//the total distance
		for (int i = 0; i < ordered.size(); i++)
		{
			//gets position in the edge list
			int edge_position = ordered[i].second;
			//use that position to find pairs between vertices
			//unite both sets between the vertices
			Set Combine = vertgroups[vertpairs[edge_position].first].Union(vertgroups[vertpairs[edge_position].second]);

			if (Combine.size() != vertgroups[vertpairs[edge_position].first].size())
			{
				dist = dist + ordered[i].first.weight;
			}

			for (int j = 0; j < vertices.size(); j++)
			{
				if (Combine.find(vertices[j]))
				{
					vertgroups[j] = Combine;
				}
			}
			if (vertgroups[vertpairs[edge_position].first].size() == nV)
				return dist;
		}
		return dist;
	}
};

int main()
{
	int nVertices = 0;
	//input number of vertices
	cin >> nVertices;

	if (nVertices == 0 || nVertices == 1)
	{
		cout << "0.000000000" << endl;
		return 0;
	}

	Graph g(nVertices);
	//x,y co-ordinates
	double x = 0;
	double y = 0;

	for (int i = 0; i < nVertices; i++)
	{
		//enter x,y co-ordinates and update the graph accordingly
		cin >> x >> y;
		g.addvert(x, y);
	}

	g.MakeEdges();
	cout << fixed;
	cout << setprecision(9);
	cout << g.KruskalDist() << endl;
    return 0;
}

