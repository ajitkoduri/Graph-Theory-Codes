// AoG HW 1.2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <vector>
//creating a set class so that we can quickly find whether a vertex has been previously crossed or not
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

//function to find number of connected components:
//I look into a vertex and all vertices it's connected to. 

//Every time that I found all the vertices it's connected to,
//I add 1 to the number of connected components find a new unexplored vertex to then restart this process.
//I initialize the code to start looking from the vertex labelled 1.

//In the case that that vertex is not connected to any vertex, the program will double count that point.
//This is because the number of connected components is initialized to 1,
//so I'm already counting the vertex 1. 

//When it's found that it has no connections to anything else,
//it will add 1 to the number of connected components.


//To combat that, I just subtract 1 from the number of connected components if vertex 1 is not connected
//to another other vertex.
int ConComp(std::vector <std::stack <int> > vlist)
{
	//there are at least 1 connected components in each graph
	int numSets = 1;
	std::stack <int> ancestors;
	//starting at arbitrary vertex named 1
	int current_vert = 1;
	int start = 1;
	ancestors.push(1);
	set vertpassed;
	vertpassed.push(0);
	//while there are still previous vertices to look into

	//to avoid double counting of when our initial starting point is unconnected to anything else
	//I subtract 1
	if (vlist[1].empty())
	{
		numSets--;
	}

	while (!ancestors.empty())
	{
		//look in vertex list to see all vertices that can be found in chain 
		if (!vlist[start].empty())
		{
			current_vert = vlist[start].top();
			vlist[start].pop();
			start = current_vert;
			ancestors.push(start);
			vertpassed.push(start);
		}
		//once all edges connected to a vertex are cleared up, look into its ancestor's edges
		else
		{
			while (vlist[ancestors.top()].empty())
			{
				ancestors.pop();
				//if there are no more ancestors to look into, see if there are any unexplored vertices to look into
				if (ancestors.empty())
				{
					for (int i = 1; i < vlist.size(); i++)
					{
						if (!vertpassed.find(i))
						{
							//start new ancestors list with this new vertex
							ancestors.push(i);
							//add this vertex to the ones that have been passed
							vertpassed.push(i);
							start = i;
							numSets++;
							break;
						}
					}
					//if no vertices not passed, return number of connected components
					if (ancestors.empty())
					{
						return numSets;
					}
				}
			}
			//if we've passed through all the vertices at least once, return the number of connected components
			if (vertpassed.length() == vlist.size())
			{
				return numSets;
			}
			start = ancestors.top();
		}
	}
	return numSets;
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
		vertices[end_vert].push(start_vert);
	}

	//find number of connected components
	std::cout << ConComp(vertices) << std::endl;

	return 0;
}

