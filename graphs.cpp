#include "graphs.hpp"

_Edge_::_Edge_() { this->Weight = 0; }
_Edge_::_Edge_(int tV, int W)
{
	this->toVertex = tV;
	Weight = W;
}

Graph::Graph() { this->Vertex = 0; }
Graph::Graph(int Vertex)
{
	this->Vertex = Vertex;
	E = new vector<_Edge_>[Vertex];
}
void Graph::getEdge(int va, int vb, int weight)
{
	_Edge_ temp(vb, weight);
	E[va].push_back(temp);
}
void Graph::DFS(int v, bool visited[])
{
	visited[v] = true;
	// Syntax for traversal of a vector
	for (auto &iter : E[v])
		if (!visited[iter.toVertex])
			DFS(iter.toVertex, visited);
}
void Graph::printAdj()
{
	int Adj[SIZE][SIZE], v = 0, v1;
	for (; v < Vertex; v++)
		for (v1 = 0; v1 < Vertex; v1++)
			Adj[v][v1] = 0;
	for (v = 0; v < Vertex; v++)
		for (auto &iter : E[v])
			Adj[v][iter.toVertex] = iter.Weight;
	for (v = 0; v < Vertex; v++)
	{
		for (v1 = 0; v1 < Vertex; v1++)
			cout << Adj[v][v1] << " ";
		cout << endl;
	}
}
int Graph::no_of_Components()
{
	int k = 0, v = 0;
	bool *visited = new bool[Vertex];
	for (; v < Vertex; v++)
		visited[v] = false;
	for (v = 0; v < Vertex; v++)
		if (visited[v] == false)
		{
			DFS(v, visited);
			k++;
		}
	return k;
}
// bool hasCircuit();  // Needs code, ig Girish can
_Edge_ Graph::minW(int v, bool *visited)
{
	_Edge_ temp;
	temp.Weight = INT_MAX;
	for (auto &iter : E[v])
		if (!visited[iter.toVertex] && temp.Weight >= iter.Weight)
			temp = iter;
	visited[temp.toVertex] = true;
	return temp;
}