#include<fstream>
#include<vector>
#include<list>
#include<stack>
#include<algorithm>
#include<climits>
using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

class Graph
{
public:
	int n_nodes;
	vector<int> vertices_time; // merge vertices+adj (vector<pair<int,list<int>>> -- int - time, list - adj)
	vector<list<int>> adj;
	vector<bool> visited;
	stack<int> order;
	vector<vector<int>> result;

	Graph() 
	{
		ifstream input;
		input.open(iname);
		input >> n_nodes;
		vertices_time.resize(n_nodes);
		adj.resize(n_nodes);
		visited.resize(n_nodes);
		result.resize(n_nodes);

		for (int i = 0; i < n_nodes; i++)
		{
			int t;
			input >> t;
			vertices_time[i] = (t);
			visited[i] = false;
		}
		for (int i = 0; i < n_nodes; i++)
		{
			for (int j = 0; j < n_nodes; j++)
			{
				result[i].resize(n_nodes);
				int is_inc;
				input >> is_inc;
				if (is_inc == 1)
					adj[i].push_back(j); // -1!
			}
		}
		for (int i = 0; i < n_nodes; i++)
		{
			for (int j = 0; j < n_nodes; j++)
			{
				if (i == j)
					result[i][j] = INT_MIN;
				else result[i][j] = 0;
			}
		}
	}

	void top_sort(int v)
	{
		visited[v] = true;
		for (int a : adj[v])
			if (!visited[a])
				top_sort(a);
		order.push(v);
	}

	//int get_edge_weight(int from, int to)
	//{
	//	if (find(adj[from].begin(), adj[from].end(), to) != adj[from].end())
	//	{
	//		return(vertices_time[from] + vertices_time[to]); // smert
	//	}
	//	return -1;
	//}

	void out()
	{
		ofstream output;
		output.open(oname);
		output.clear();


		for (int i = 0; i < n_nodes; i++)
		{
			for (int j = 0; j < n_nodes; j++)
			{
				if (result[i][j] == INT_MIN)
					result[i][j] = 0; // FU MDA
				if (result[i][j] != 0)
					result[i][j] += vertices_time[i];
				output << result[i][j] << " ";
			}
			output << endl;
		}
	}

	void get_res(int start_node)
	{
		for (int i = 0; i < n_nodes; i++)
		{
			visited[i] = false;
		}

		for (int i = 0; i < n_nodes; i++)
		{
			if (!visited[i])
				top_sort(i);
		}

		for (int i = 0; i < n_nodes; i++)
		{
			result[start_node][i] = INT_MIN;
		}
		result[start_node][start_node] = 0;

		while (!order.empty())
		{
			int v = order.top();
			order.pop();

			if (result[start_node][v] != INT_MIN)
			{
				for (int a : adj[v])
				{
					int wa = result[start_node][a];
					int wv = result[start_node][v];
					int timea = vertices_time[a];
					if (wa < wv + timea)
						result[start_node][a] = wv + timea;
				}
			}
		}
	}

};

int main()
{
	Graph graph = Graph();
	for (int i = 0; i < graph.n_nodes; i++)
	{
		graph.get_res(i);
	}
	graph.out();
	//getchar();
}