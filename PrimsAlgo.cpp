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

	_Edge_() { this->Weight = 0; }
	_Edge_(int tV, int W)
	{
		this->toVertex = tV;
		Weight = W;
	}
};
class Graph
{
public:
	int Vertex; // no. of vertices
	vector<_Edge_> *E;

	Graph() { this->Vertex = 0; }
	Graph(int Vertex)
	{
		this->Vertex = Vertex;
		E = new vector<_Edge_>[Vertex];
	}
	void getEdge(int va, int vb, int weight)
	{
		_Edge_ temp(vb, weight);
		E[va].push_back(temp);
	}
	void DFS(int v, bool visited[])
	{
		visited[v] = true;

		// Syntax for traversal of a vector
		for (auto &iter : E[v])
			if (!visited[iter.toVertex])
				DFS(iter.toVertex, visited);
	}
	void printAdj()
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
	int no_of_Components()
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
	_Edge_ minW(int v, bool *visited)
	{
		_Edge_ temp;
		temp.Weight = INT_MAX;

		for (auto &iter : E[v])
			if (!visited[iter.toVertex] && temp.Weight >= iter.Weight)
				temp = iter;
		visited[temp.toVertex] = true;

		return temp;
	}
};

Graph PrimsAlgo(Graph G)
{
	Graph G2(G.Vertex);

	if (G.no_of_Components() != 1)
	{
		cout << "\n\nNo Spanning Tree possible for the given Graph\n\n";
		return G2;
	}

	int v, v1, v2;
	_Edge_ e1, e2, minWedge;
	minWedge.Weight = INT_MAX;
	bool *visited = new bool[G.Vertex];
	for (v = 0; v < G.Vertex; v++)
		visited[v] = false;

	for (v = 0; v < G.Vertex; v++)
		for (auto &iter : G.E[v])
			if (minWedge.Weight <= iter.Weight)
			{
				minWedge = iter;
				v1 = v;
				v2 = minWedge.toVertex;
			}
	visited[v1] = true;
	visited[v2] = true;
	G2.getEdge(v1, v2, minWedge.Weight);
	cout<<"::"<<v1<<":"<<v2<<";";

	for (int c = 0; c < G.Vertex - 1; c++)
	{
		e1 = G.minW(v1, visited);
		e2 = G.minW(v2, visited);

		if (e1.Weight < e2.Weight)
		{
			G2.getEdge(v1, e1.toVertex, e1.Weight);
			v1 = e1.toVertex;
		}
		else
		{
			G2.getEdge(v2, e2.toVertex, e2.Weight);
			v2 = e2.toVertex;
		}
	}

	return G2;
}

int main()
{

	int Adj[SIZE][SIZE]={{0,2,0,0},{2,0,1,0},{0,1,0,0},{0,0,0,0}}, i = 0, j = 0, n=4;
	// cin >> n;
	Graph g(n); // Declaration after input for `n` is got
	for (; i < n; i++)
		for (j = 0; j < n; j++)
		{
			// cin >> Adj[i][j];
			if (Adj[i][j])
				g.getEdge(i, j, Adj[i][j]);
		}

	cout << endl; // For now it just prints no. of components as output
	PrimsAlgo(g).printAdj();

	return 0;
}