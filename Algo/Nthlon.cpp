#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_V 410
#define INF 99999

const int START = 401;

vector<pair<int, int>> adj[MAX_V];

int vertex(int delta);
int solve(vector<int> & a, vector<int> & b);
vector<int> dijkstra(const int src);

int main()
{
	int caseNum;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		vector<int> a, b;

		int n;
		cin >> n;

		int aTime, bTime;
		for (int nIter = 0; nIter < n; nIter++)
		{
			cin >> aTime >> bTime;
			a.push_back(aTime);
			b.push_back(bTime);
		}

		int shortest = solve(a, b);

		if (shortest == INF)
		{
			cout << "IMPOSSIBLE";
		}
		else
		{
			cout << shortest << endl;
		}
	}
}

int vertex(int delta)
{
	return delta + 200;
}

int solve(vector<int> & a, vector<int> & b)
{
	for (int i = 0; i < 402; i++) { adj[i].clear(); }

	// Create Graph from START vertex
	for (int i = 0; i < a.size(); i++)
	{
		int delta = a[i] - b[i];

		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}

	// Create Graph from all real vertex
	for (int delta = -200; delta <= 200; delta++)
	{
		for (int i = 0; i < a.size(); i++)
		{
			int next = delta + a[i] - b[i];

			if (abs(next) > 200) continue;

			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}

	vector<int> dist = dijkstra(START);

	return dist[vertex(0)];
}

vector<int> dijkstra(const int src)
{
	vector<int> dist(MAX_V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));

	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			int nextCost = cost + adj[here][i].second;

			if (dist[there] > nextCost)
			{
				pq.push(make_pair(-nextCost, there));
				dist[there] = nextCost;
			}
		}

	}

	return dist;
}

