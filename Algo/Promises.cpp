#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 200
#define MAX_M 1000
#define MAX_N 1000
#define INF 99999

using namespace std;

struct path_info {
	int a;
	int b;
	int c;
}typedef path_info;

int adj[MAX_V][MAX_V];
vector<path_info> new_adjs;

int shortest_adj[MAX_V][MAX_V];
int shortest_new_adj[MAX_V][MAX_V];

int solve(int v);
void floyd(int param_adj[MAX_V][MAX_V], int v);

int main()
{
	int caseNum;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int v, m, n;
		cin >> v >> m >> n;

		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				adj[i][j] = INF;

		new_adjs.clear();

		int a, b, c;
		for (int mi = 0; mi < m; mi++)
		{
			cin >> a >> b >> c;

			adj[a][b] = c;
			adj[b][a] = c;
		}

		for (int ni = 0; ni < n; ni++)
		{
			cin >> a >> b >> c;

			path_info info;
			info.a = a;
			info.b = b;
			info.c = c;

			new_adjs.push_back(info);
		}

		int uselessRoadCount = solve(v);

		cout << uselessRoadCount << endl;
	}
}

int solve(int v)
{
	int uselessCnt = 0;

	for (int i = 0; i < new_adjs.size(); i++)
	{
		// calculate original shortest paths
		int origin_shortest[MAX_V][MAX_V];

		for (int j = 0; j < v; j++)
			for (int k = 0; k < v; k++)
				origin_shortest[j][k] = adj[j][k];

		floyd(origin_shortest, v);

		// calculate new shortest paths
		int new_shortest[MAX_V][MAX_V];

		for (int j = 0; j < v; j++)
			for (int k = 0; k < v; k++)
				new_shortest[j][k] = adj[j][k];

		int a = new_adjs[i].a;
		int b = new_adjs[i].b;
		int c = new_adjs[i].c;

		new_shortest[a][b] = c;
		new_shortest[b][a] = c;

		floyd(new_shortest, v);

		// set adj for next step
		adj[a][b] = c;
		adj[b][a] = c;

		// Check whether usable
		bool usable = false;
		for (int j = 0; j < v; j++)
			for (int k = 0; k < v; k++)
				if ((origin_shortest[j][k] == INF && new_shortest[j][k] != INF) ||
					(origin_shortest[j][k] > new_shortest[j][k]))
				{
					usable = true;
				}

		if (!usable) uselessCnt++;
	}

	return uselessCnt;
}

void floyd(int param_adj[MAX_V][MAX_V], int v)
{
	for (int i = 0; i < v; i++)
		param_adj[i][i] = 0;

	for (int k = 0; k < v; k++)
		for (int i = 0; i < v; i++)
		{
			if (param_adj[i][k] == INF) continue;

			for (int j = 0; j < v; j++)
			{
				param_adj[i][j] = min(param_adj[i][j], param_adj[i][k] + param_adj[k][j]);
			}
		}
}

int V, adj[200][200];

bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;

	for (int x = 0; x < V; x++)
		for (int y = 0; y < V; y++)
			adj[x][y] = min(adj[x][y],
				min(adj[x][a] + c + adj[b][y],
					adj[x][b] + c + adj[a][y]));

	return true;
}