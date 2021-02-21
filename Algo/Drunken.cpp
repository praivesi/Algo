#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 500
#define INF 99999

using namespace std;

// first - vertex, second - cost
int adj[MAX_V][MAX_V];
int W[MAX_V][MAX_V];
vector < pair<int, int>> order;
int delay[MAX_V];
int v, e;

void solve();

int main()
{
	cin >> v >> e;

	int delayInput;
	for (int i = 0; i < v; i++)
	{
		cin >> delayInput;

		delay[i] = delayInput;
	}

	for (int i = 0; i < v; i++)
	{
		order.push_back(make_pair(delay[i], i));
	}

	sort(order.begin(), order.end());

	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			adj[i][j] = INF;

	int a, b, c;
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b >> c;

		adj[a - 1][b - 1] = c;
		adj[b - 1][a - 1] = c;
	}

	int caseNum;
	cin >> caseNum;

	int s, t;

	solve();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> s >> t;

		cout << "s -> t: " << W[s - 1][t - 1] << endl;
	}
}

void solve()
{
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			W[i][j] = i == j ? 0 : adj[i][j];
		}
	}

	for (int k = 0; k < v; k++)
	{
		for (int i = 0; i < v; i++)
		{
			int w = order[k].second;

			for (int j = 0; j < v; j++)
			{
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(W[i][j], adj[i][w] + delay[w] + adj[w][j]);
			}
		}
	}
}