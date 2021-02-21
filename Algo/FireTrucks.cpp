#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_V 1001
#define INF 99999

vector<int> truckLocations;
vector<int> fireLocations;

// first - adj vertex, second - cost
vector<pair<int, int>> adj[MAX_V];

vector<int> dijkstraModified();

int main()
{
	int caseNum;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		truckLocations.clear();
		fireLocations.clear();

		for (int i = 0; i < MAX_V; i++)
		{
			adj[i].clear();
		}

		int v, e, n, m;

		cin >> v >> e >> n >> m;

		int a, b, t;
		for (int eIter = 0; eIter < e; eIter++)
		{
			cin >> a >> b >> t;

			adj[a].push_back(make_pair(b, t));
			adj[b].push_back(make_pair(a, t));
		}

		int nNum;
		for (int nIter = 0; nIter < n; nIter++)
		{
			cin >> nNum;
			fireLocations.push_back(nNum);
		}

		int mNum;
		for (int mIter = 0; mIter < m; mIter++)
		{
			cin >> mNum;
			truckLocations.push_back(mNum);
		}

		vector<int> dist = dijkstraModified();

		int timeSum = 0;
		for (int fireIdx = 0; fireIdx < fireLocations.size(); fireIdx++)
		{
			timeSum += dist[fireLocations[fireIdx]];
		}

		cout << timeSum << endl;
	}
}

vector<int> dijkstraModified()
{
	// first => cost * -1, second => vertex
	priority_queue<pair<int, int>> pq;
	vector<int> dist(MAX_V, INF);

	for (int truckIdx = 0; truckIdx < truckLocations.size(); truckIdx++)
	{
		adj[0].push_back(make_pair(truckLocations[truckIdx], 0));
	}

	pq.push(make_pair(0, 0));
	dist[0] = 0;

	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int adjIdx = 0; adjIdx < adj[here].size(); adjIdx++)
		{
			int there = adj[here][adjIdx].first;
			int nextCost = cost + adj[here][adjIdx].second;

			if (dist[there] > nextCost)
			{
				pq.push(make_pair(-1 * nextCost, there));
				dist[there] = nextCost;
			}
		}
	}

	return dist;
}