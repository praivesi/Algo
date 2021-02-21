#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 100
#define INF 99999

using namespace std;

// first - vertex, second - cost
vector<pair<int, int>> adj[MAX_V];
bool reachable[MAX_V][MAX_V];

void floyd(int vCnt);
int bellman2(int src, int target, int vCnt);

int main()
{
	int caseNum;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		for (int i = 0; i < MAX_V; i++) { adj[i].clear(); }

		int g, w;
		cin >> g >> w;

		int a, b, d;
		for (int wIter = 0; wIter < w; wIter++)
		{
			cin >> a >> b >> d;

			adj[a].push_back(make_pair(b, d));
		}

		floyd(g);

		int distance = bellman2(0, 1, g);
		
		// reverse input
		for (int here = 0; here < g; here++)
			for (int i = 0; i < adj[here].size(); i++)
				adj[here][i].second *= -1;

		floyd(g);

		int reverse_distance = bellman2(0, 1, g);

		if (distance == INF || distance == -INF)
		{
			cout << "UNREACHABLE" << endl;
		}
		else
		{
			cout << distance << " ";

			if (reverse_distance == INF || reverse_distance == -INF)
			{
				cout << "INFINITY" << endl;
			}
			else
			{
				cout << reverse_distance << endl;
			}
		}
	}
}

int bellman2(int src, int target, int vCnt)
{
	vector<int> upper(MAX_V, INF);
	upper[src] = 0;

	for (int iter = 0; iter < vCnt - 1; iter++)
	{
		for (int here = 0; here < vCnt; here++)
		{
			for (int i = 0; i < adj[here].size(); i++)
			{
				int there = adj[here][i].first;
				int cost = adj[here][i].second;

				upper[there] = min(upper[here] + cost, upper[there]);
			}
		}
	}

	for (int here = 0; here < vCnt; here++)
	{
		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			int cost = adj[here][i].second;

			if (upper[here] + cost < upper[there]) // exist negative cycle
			{
				if (reachable[src][here] && reachable[here][target])
				{
					return -INF;
				}
			}
		}
	}

	return upper[target];
}

void floyd(int vCnt)
{
	int tmpAdj[MAX_V][MAX_V];

	// Initialize
	for (int i = 0; i < vCnt; i++)
	{
		for (int j = 0; j < vCnt; j++)
		{
			if (i == j)
			{
				tmpAdj[i][j] = 0;
				continue;
			}

			tmpAdj[i][j] = INF;
		}
	}

	for (int here = 0; here < vCnt; here++)
	{
		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			int cost = adj[here][i].second;

			tmpAdj[here][there] = cost;
		}
	}

	// floyd
	for (int k = 0; k < vCnt; k++)
	{
		for (int i = 0; i < vCnt; i++)
		{
			if (tmpAdj[i][k] == INF) continue;

			for (int j = 0; j < vCnt; j++)
			{
				tmpAdj[i][j] = min(tmpAdj[i][j], tmpAdj[i][k] + tmpAdj[k][j]);
			}
		}
	}

	// set reachable[][]
	for (int i = 0; i < vCnt; i++)
		for (int j = 0; j < vCnt; j++)
			reachable[i][j] = tmpAdj[i][j] == INF ? false : true;
}