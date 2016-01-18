#include <iostream>
#include <list>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <ctime>

#ifndef _MAZE_GENERATOR_H
#define _MAZE_GENERATOR_H


class Graph
{

public:

	struct removed{
		int a;
		int b;
	}temp;

	std::vector<removed> ab;

	int V;    // No. of vertices
	//list<int> *adj;    // Pointer to an array containing adjacency lists
	// A function used by DFS
	std::vector<int> *adj;
	bool DFSUtil(int v, bool visited[]);
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void DFS(int v);
	std::vector<int> *getRemoved();
	Graph();
	//void DFS(int v);    // DFS traversal of the vertices reachable from v
	//int removeEdge(int v, int index);
}g;

#endif _MAZE_GENERATOR_H