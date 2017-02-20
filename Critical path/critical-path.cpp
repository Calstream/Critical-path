#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#include<stack>
#include<algorithm>
#include<stack>
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
	//stack<int> order;
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
		
	}

	/*void AddVertex(char v)
	{
		if (adj.find(v) == adj.end())
		{
			++Size;
			adj.emplace(pair<char, list<char>>(v, *(new list<char>())));
			visited.emplace(pair<char, bool>(v, false));
			used.emplace(pair<char, int>(v, 0));
		}
	}*/

	//void AddEdge(char v1, char v2)
	//{
	//	if (v1 == '\0' || v2 == '\0')
	//		return;
	//	if (find(adj[v1].begin(), adj[v1].end(), v2) == adj[v1].end())
	//		adj[v1].emplace_back(v2);
	//}

	/*void top_sort_ut(int v)
	{
		visited[v] = true;
		for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				top_sort_ut(*i);
		order.push(v);
	}

	void top_sort()
	{
		for (auto v : adj)
			if (!visited[v.first])
				top_sort_ut(v.first);
		ofstream output;
		output.open(oname);
		output.clear();
		for (int i = order.size() - 1; i >= 0; --i)
			output << order[i];
	}*/

	void get_res(int start_node)
	{
		stack<int> order;
		for (int i = 0; i < n_nodes; i++)
		{
			for (int j = 0; j < n_nodes; i++)
			{
				if (i == j)
					result[i][j] = 0;
				else result[i][j] = INT_MIN;
			}
		}
		for (int i = 0; i < n_nodes; i++)
		{

		}
	}

};

//void make_vertices(string s, Graph & G)
//{
//	for (int i = 0; i < s.length(); i++)
//	{
//		G.AddVertex(s[i]);
//	}
//}


int main()
{
	Graph graph = Graph();
	ofstream output;
	output.open(oname);
	output.clear();
	output << "-";
	getchar();
}