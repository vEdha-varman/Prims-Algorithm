#include <iostream>
#include <climits>
#include <vector>

#define SIZE 10

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
	_Edge_ minW(int v, bool visited[])
	{
		_Edge_ temp(-1,INT_MAX);

		// for a given vertex, we traverse through all vertices
		for (auto &iter : E[v]){
			// To find the least weighted vertex leading to an unreached vertex
			if (!visited[iter.toVertex] && temp.Weight >= iter.Weight)
			{
				temp = iter;
			}}

		return temp;
	}
	void printlst()
	{
		for(int v=0; v < Vertex; v++){
			cout<<v+1;
		for (auto &iter : E[v]){
			cout<<" ::"<<iter.toVertex+1<<","<<iter.Weight;
			}
			cout<< "\n";
		}
	}

};

Graph PrimsAlgo(Graph G)
{
	Graph G2(G.Vertex);

	// Disconnected graph case
	if (G.no_of_Components() != 1)
	{
		cout << "\n\nNo Spanning Tree possible for the given Graph\n\n";
		return G2;
	}

	int v, v1, v2;
	_Edge_ e, minWedge;
	minWedge.Weight = INT_MAX;
	bool *visited = new bool[G.Vertex];
	for (v = 0; v < G.Vertex; v++)
		visited[v] = false;

	// insert the least weighted edge as the first
	for (v = 0; v < G.Vertex; v++)
		for (auto &iter : G.E[v])
			if (minWedge.Weight >= iter.Weight)
			{
				minWedge = iter;
				v1 = v;
				v2 = minWedge.toVertex;
			}
	visited[v1] = true;
	visited[v2] = true;
	G2.getEdge(v1, v2, minWedge.Weight);
	G2.getEdge(v2, v1, minWedge.Weight);

	// To pick the rest V-2 edges apart from the first one
	for (int c = 0; c < G.Vertex - 2; c++)
	{
		// To find the minimum weighted edge starting from a reached vertex ending at an unreached vertex
		for(v=0, minWedge={-1,INT_MAX}; v<G.Vertex; v++)
		{
			if(visited[v])
			{
				e = G.minW(v, visited);
				if(minWedge.Weight >= e.Weight)
				{
					minWedge = e;
					v1 = v;
				}
			}
		}
		// This case is to avoid addition of default all-unvisited-vetices case
		if(minWedge.toVertex != -1)
		{
			G2.getEdge(v1, minWedge.toVertex, minWedge.Weight);
			G2.getEdge(minWedge.toVertex, v1, minWedge.Weight);
			visited[minWedge.toVertex] = true;
		}
	}

	return G2;
}

int main()
{

	int Adj[SIZE][SIZE]={{0,28,0,0,0,10,0,0},{28,0,16,0,0,0,14,0},{0,16,0,12,0,0,0,0},{0,0,12,0,22,0,18,0},{0,0,0,22,0,25,13,0},{10,0,0,0,25,0,0,0},{0,14,0,18,13,0,0,99},{0,0,0,0,0,0,99,0}}; 
	int i = 0, j = 0, n=8;
	// cin >> n;
	Graph g(n); // Declaration after input for `n` is got
	for (; i < n; i++)
		for (j = 0; j < n; j++)
		{
			// cin >> Adj[i][j];
			if (Adj[i][j])
				g.getEdge(i, j, Adj[i][j]);
		}
	cout<< "Given input:: fromVertex: toVertex, Weight:\n";
	g.printlst();
	cout << endl; // For now it just prints no. of components as output
	cout<< "\n\nSpanning tree's Adjacency Matrix:\n";
	PrimsAlgo(g).printAdj();

	return 0;
}