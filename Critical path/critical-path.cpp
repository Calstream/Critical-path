#include<fstream>
#include<vector>
#include<list>
#include<stack>
#include<algorithm>
#include<climits>
#include<queue>
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
	vector<int> indegree;
	queue<int> ind_0; // vertices with indegree == 0
	queue<int> order;
	vector<int> result;

	Graph()
	{
		ifstream input;
		input.open(iname);
		input >> n_nodes;
		vertices_time.resize(n_nodes);
		adj.resize(n_nodes);
		visited.resize(n_nodes);
		result.resize(n_nodes);
		indegree.resize(n_nodes);

		for (int i = 0; i < n_nodes; i++) // O(V) ?
		{
			int t;
			input >> t;
			vertices_time[i] = (t);
			visited[i] = false;
		}

		for (int i = 0; i < n_nodes; i++)
		{
			for (int j = 0; j < n_nodes; j++) // O(V^2) ?
			{
				int is_inc;
				input >> is_inc;
				if (is_inc == 1)
				{
					adj[i].push_back(j); // -1!
					++indegree[j];
				}
			}
		}
	}

	void top_sort() // O(V+E)
	{
		for (int i = 0; i < n_nodes; i++)
		{
			if (indegree[i] == 0)
			{
				ind_0.push(i);
				indegree[i] = -1;
			}
		}
		auto temp = adj;
		while (!ind_0.empty())
		{
			int v = ind_0.front();
			ind_0.pop();
			order.push(v);
			for (int a : temp[v])
				--indegree[a]; // reduce indegree of adjacent vertices and 
			temp[v].clear(); // }:(						remove v from graph
			for (int i = 0; i < n_nodes; i++)
			{
				if (indegree[i] == 0)
				{
					ind_0.push(i);
					indegree[i] = -1;
				}
			}
		}
	}

	// one line
	void get_result_i(int start_node)
	{
		for (int i = 0; i < n_nodes; i++)
		{
			result[i] = INT_MIN;
		}
		result[start_node] = 0;

		queue<int> order_c = order;
		while (!order_c.empty())
		{
			int v = order_c.front();
			order_c.pop();

			if (result[v] != INT_MIN)
			{
				for (int a : adj[v])
				{
					int wa = result[a];
					int wv = result[v];
					int timea = vertices_time[a];
					if (wa < wv + timea)
						result[a] = wv + timea;
				}
			}
		}
		for (int i = 0; i < n_nodes; i++)
		{
			if (result[i] == INT_MIN)
				result[i] = 0;
			else if (result[i] != 0)
				result[i] += vertices_time[start_node];
		}
	}

	// get res and write to file
	void out()
	{
		ofstream output;
		output.open(oname);
		output.clear();
		// all lines
		for (int i = 0; i < n_nodes; i++)
		{
			get_result_i(i);
			for (int j = 0; j < n_nodes; j++)
			{
				output << result[j] << " ";
			}
			output << endl;
		}
	}
};

int main()
{
	Graph graph;
	graph.top_sort();
	graph.out();
}