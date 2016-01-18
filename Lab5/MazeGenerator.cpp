#include <iostream>
#include <list>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include "MazeGenerator.h"

Graph::Graph(){

}

Graph::Graph(int V)
{
	this->V = V;
	adj = new std::vector<int>[V*V];
	srand((unsigned int)time(0));
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

bool Graph::DFSUtil(int v, bool visited[])
{
	if (v == V*V-1){
		int count = 0;
		for (int t = 0; t < V*V; t++)
		if (visited[t]) count++;
		if (2* count < V*V) return false;
		return true;
	}

	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	
	
	random_shuffle(adj[v].begin(), adj[v].end()); 
	std::vector<int>::iterator i = adj[v].begin();
	
	while (i != adj[v].end()){
		int j = *i;

		if (!visited[j]){
			std::vector <int>::iterator k = find(adj[j].begin(), adj[j].end(), v);
			adj[j].erase(adj[j].begin() + distance(adj[j].begin(), k));
			i = adj[v].erase(i);

			//
			temp.a = j;
			temp.b = v;

			ab.push_back(temp);
			//

			if (DFSUtil(j, visited))return true;

		}
		else{
			i++;
		}
	}
		

	return false;
}


void Graph::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V*V];
	for (int i = 0; i < V*V; i++)
		visited[i] = false;

	// Call the recursive helper function to print DFS traversal
	DFSUtil(v, visited);
}



std::vector<int> *Graph::getRemoved(){
//	int n = 9;
	// Create a graph given in the above diagram
//	Graph g(n);

	for (int i = 0; i < V; i++){
		for (int j = 0; j < V; j++){

			if (i - 1 >= 0){
				addEdge(V * i + j, V * (i - 1) + j);
			}
			if (i + 1 <= V-1){
				addEdge(V * i + j, V * (i + 1) + j);
			}
			if (j - 1 >= 0){
				addEdge(V * i + j, V * i + j-1);
			}
			if (j + 1 <= V-1){
				addEdge(V * i + j, V * (i) + j+1);
			}
		}
	}
	DFS(0);
	
	for (int v = 0; v < V*V; v++){
		
		std::cout << "v=" << v << ":";
		
		std::vector<int>::iterator i = adj[v].begin();
		while (i != adj[v].end()){
			std::cout << *i <<" ";
			i++;
		}
		std::cout << '\n';
	}

	//cout << "Following is Depth First Traversal (starting from vertex 2) \n";
	return adj;
}