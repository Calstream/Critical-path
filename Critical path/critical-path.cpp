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
	queue<int> ind_0;
	//stack<int> order;
	queue<int> order;
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
		indegree.resize(n_nodes);

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
				{
					adj[i].push_back(j); // -1!
					++indegree[j];
				}
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

	void top_sort_ut(int v)
	{
		getchar();
		visited[v] = true;
		getchar();
		for (int a : adj[v])
			if (!visited[a])
				top_sort_ut(a);
		order.push(v);
	}

	void top_sort() // check indegree
	{
		for (int i = 0; i < n_nodes; i++)
		{
			visited[i] = false;
		}
				top_sort_ut(0);
	}

	void new_top_sort()
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
				--indegree[a];
			temp[v].clear(); // congratulations, you played yourself
			for (int i = 0; i < n_nodes; i++)
			{
				if (indegree[i] == 0)
				{
					ind_0.push(i);
					indegree[i] = -1;
				}
			}
		}

		/* Store each vertex’s In-Degree in an array
		2. Initialize a queue with all in-degree zero vertices
		3. While there are vertices remaining in the queue: 
		Dequeue and output a vertex 
		Reduce In-Degree of all vertices adjacent to it by 1
		Enqueue any of these vertices whose In-Degree became zero */
	}

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
			result[start_node][i] = INT_MIN;
		}
		result[start_node][start_node] = 0;

		queue<int> order_c = order;
		while (!order_c.empty())
		{
			int v = order_c.front();
			order_c.pop();

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
	//graph.top_sort();
	graph.new_top_sort();
	for (int i = 0; i < graph.n_nodes; i++)
	{
		graph.get_res(i);
	}
	graph.out();
	//getchar();
}