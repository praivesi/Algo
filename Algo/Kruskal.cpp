#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#define MAX_V 99999
#define INF 987654321

using namespace std;

double kruskalExtension(vector<pair<int, int>> & selected, vector<pair<int, int>> & preConnected);
int prim(vector<pair<int, int>> & selected);

typedef struct DisjointSet
{
	vector<int> parent, rank;

	DisjointSet(int n) : parent(n), rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int u)
	{
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v)
	{
		u = find(u), v = find(v);
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;

		if (rank[u] == rank[v]) ++rank[v];
	}
} DisjointSet;


int V; // vertex count
vector<pair<int, double>> adj[MAX_V] ;// (v, cost)

int main()
{
	int caseNum;
	cin >> caseNum;

	for (int ci = 0; ci < caseNum; ci++)
	{
		for (int i = 0; i < V; i++)
		{
			adj[i].clear();
		}

		int n, m;
		cin >> n >> m;

		vector<pair<int, int>> pos(n);

		for (int ni = 0; ni < n; ni++)
		{
			int x;
			cin >> x;

			pos[ni].first = x;
		}

		for (int ni = 0; ni < n; ni++)
		{
			int y;
			cin >> y;

			pos[ni].second = y;
		}

		vector<pair<int, int>> connected;
		for (int mi = 0; mi < m; mi++)
		{
			int a, b;
			cin >> a >> b;
			connected.push_back(make_pair(a, b));
		}

		V = n;
		for(int i = 0; i < V; i++)
			for (int j = i + 1; j < V; j++)
			{
				double distance = sqrt(pow(pos[i].first - pos[j].first, 2) + pow(pos[i].second - pos[j].second, 2));

				adj[i].push_back(make_pair(j, distance));
				adj[j].push_back(make_pair(i, distance));
			}
		
		vector<pair<int, int>> selected;

		double minDistance = kruskalExtension(selected, connected);

		cout << "MIN DISTANCE: " << minDistance << endl;
	}
}

double kruskalExtension(vector<pair<int, int>> & selected, vector<pair<int, int>> & preConnected) {
	double ret = 0;
	selected.clear();

	// (cost, (u, v))
	vector<pair<double, pair<int, int>>> edges;

	for (int u = 0; u < V; u++)
	{
		for (int i = 0; i < adj[u].size(); i++)
		{
			int v = adj[u][i].first;

			bool isAlreadyConnected = false;
			for (int pre = 0; pre < preConnected.size(); pre++)
			{
				if (((u == preConnected[pre].first) && (v == preConnected[pre].second)) ||
					((u == preConnected[pre].second) && (v == preConnected[pre].first)))
				{
					isAlreadyConnected = true;
					break;
				}
			}

			if (isAlreadyConnected) continue;

			double cost = adj[u][i].second;

			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	}

	sort(edges.begin(), edges.end());

	DisjointSet sets(V);

	// insert pre-connected vertices
	for (int i = 0; i < preConnected.size(); i++)
	{
		sets.merge(preConnected[i].first, preConnected[i].second);
		selected.push_back(make_pair(preConnected[i].first, preConnected[i].second));

		for (int j = 0; j < adj[preConnected[i].first].size(); j++)
		{
			// find cost of preConnected[i].second
		/*	if (adj[preConnected[i].first][j].first == preConnected[i].second)
			{
				ret += adj[preConnected[i].first][j].second;

				break;
			}*/
		}
	}

	// execute kruskal
	for (int i = 0; i < edges.size(); i++)
	{
		double cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;


		// avoid cycle
		if (sets.find(u) == sets.find(v)) continue;

		sets.merge(u, v);

		selected.push_back(make_pair(u, v));
		ret += cost;
	}

	return ret;
}

//int prim(vector<pair<int, int>> & selected) {
//	int ret = 0;
//	selected.clear();
//
//	vector<bool> added(V, false);
//	vector<int> minWeight(V, INF), parent(V, -1);
//
//	minWeight[0] = parent[0] = 0;
//	for (int iter = 0; iter < V; iter++)
//	{
//		int u = -1;
//		for (int v = 0; v < V; v++)
//		{
//			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
//				u = v;
//		}
//
//		if (parent[u] != u)
//			selected.push_back(make_pair(parent[u], u));
//		ret += minWeight[u];
//
//		for (int i = 0; i < adj[u].size(); i++)
//		{
//			int v = adj[u][i].first, weight = adj[u][i].second;
//
//			if (!added[v] && minWeight[v] > weight) {
//				parent[v] = u;
//				minWeight[v] = weight;
//			}
//		}
//	}
//
//	return ret;
//}