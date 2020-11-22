#ifndef GRAPHS
#define GRAPHS

#include <iostream>
#include <climits>
#include <vector>

#define SIZE 100

using namespace std;
class _Edge_
{
public:
	int toVertex;
	int Weight;

	_Edge_();
	_Edge_(int, int);
};
class Graph
{
public:
	int Vertex; // no. of vertices
	vector<_Edge_> *E;

	Graph();
	Graph(int Vertex);
	void getEdge(int va, int vb, int weight);
	void DFS(int v, bool visited[]);
	void printAdj();
	int no_of_Components();
	// bool hasCircuit();  // Needs code, ig Girish can
	_Edge_ minW(int v, bool *visited);
};

#endif