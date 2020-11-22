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
	// bool hasCircuit();  // Needs code, ig Girish can
	_Edge_ minW(int v, bool visited[])
	{
		_Edge_ temp(-1,INT_MAX);
		// int v = 0, vv;

		// for(; v < Vertex; v++)
		for (auto &iter : E[v]){
			cout<<"::"<<iter.toVertex+1<<","<<visited[iter.toVertex]<<";";
			if (!visited[iter.toVertex] && temp.Weight >= iter.Weight)
			{
				temp = iter;
				// vv = v;
			}}
		cout<<"#"<<temp.toVertex+1<<"%"<<temp.Weight<<";";

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

	int v, v1, v2;  // remove unused var
	_Edge_ e, minWedge;
	minWedge.Weight = INT_MAX;
	bool *visited = new bool[G.Vertex];
	for (v = 0; v < G.Vertex; v++)
		visited[v] = false;

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
	// cout<<"::"<<v1<<":"<<v2<<";";

	for (int c = 0; c < G.Vertex - 1; c++)
	{
		for(v=0, minWedge={-1,INT_MAX}; v<G.Vertex; v++)
		{
			if(visited[v])
			{
				e = G.minW(v, visited);
				cout<<"visited"<<v;
				if(minWedge.Weight >= e.Weight)
				{
					minWedge = e;
					v1 = v;
				}
			}
		}
		if(minWedge.toVertex != -1)
		{
			G2.getEdge(v1, minWedge.toVertex, minWedge.Weight);
			visited[v1] = true;
		}
	}

	return G2;
}

int main()
{

	int Adj[SIZE][SIZE]={{0,28,0,0,0,10,0,0},{28,0,16,0,0,0,14,0},{0,16,0,12,0,0,0,0},{0,0,12,0,22,0,18,0},{0,0,0,22,0,25,24,0},{10,0,0,0,0,25,0,0},{0,14,0,18,24,0,0,99},{0,0,0,0,0,0,99,0}}; 
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
	g.printAdj();
	cout << endl; // For now it just prints no. of components as output
	PrimsAlgo(g).printAdj();

	return 0;
}