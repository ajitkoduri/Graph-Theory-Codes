// AoG HW 2.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <vector>

class set
{
private:
	int size;
	std::vector <int> setarray;
public:
	//initialize set
	set()
	{
		size = 0;
	}
	//push a key into set
	void push(int nkey)
	{
		for (int i = 0; i < size; i++)
		{
			if (setarray[i] == nkey)
			{
				return;
			}
		}
		setarray.push_back(nkey);
		size++;
	}
	//pop a key from set
	void pop()
	{
		setarray.pop_back();
		size--;
	}
	//return first element of set
	int front()
	{
		return setarray[0];
	}
	//return last element of set
	int top()
	{
		return setarray[size - 1];
	}
	//return length of set
	int length()
	{
		return size;
	}
	//find if set is empty
	bool empty()
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	void clear()
	{
		size = 0;
		setarray.clear();
	}
	bool find(int key)
	{
		for (int i = 0; i < setarray.size(); i++)
		{
			if (key == setarray[i])
				return true;
		}

		return false;
	}
};

//we are trying to see if there is at least 1 point in a graph that can cycle back to itself
//in order to determine this, we will create a function that can explore 1 point to another
//then, we will explore each point to see if it can reference itself
//if it can, then we are done - output 1
//if none of them can, then there is no cycle in the graph

//explore function
bool Explore(std::vector <std::stack <int>> vlist, int begin, int end)
{
	std::stack <int> ancestors;
	int current_vertex = begin;
	int start = begin;
	ancestors.push(start);

	while (!ancestors.empty())
	{
		//look in vertex list to see if end product can be found in chain 
		if (!vlist[start].empty())
		{
			current_vertex = vlist[start].top();
			if (current_vertex == end)
			{
				return 1;
			}
			vlist[start].pop();
			start = current_vertex;
			ancestors.push(start);
		}
		else
		{
			//if not there, look at previously visited vertex to try again
			while (vlist[ancestors.top()].empty())
			{
				ancestors.pop();
				//if no more vertices to look into, it can't be found
				if (ancestors.empty())
				{
					return 0;
				}
			}
			//start from that vertex
			start = ancestors.top();
		}
	}
}
//check all explorations from each point to itself
bool CycDep(std::vector <std::stack <int>> vlist)
{	
	for (int i = 0; i < vlist.size(); i++)
	{
		if (Explore(vlist, i, i) == 1)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	//creating variables to be used to find out if vertices in path are connected
	int nVertices = 0;
	int mEdges = 0;
	int start_vert = 0;
	int end_vert = 0;
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
	}

	//determine if there is a cyclic dependence in graph or not
	std::cout << CycDep(vertices) << std::endl;
    return 0;
}

