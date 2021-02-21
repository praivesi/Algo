#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_V 10000
#define INF 99999

vector<pair<int, float>> adj[MAX_V];

vector<float> dijkstra(int v, int src);

int main()
{
	int caseNum;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int n, m;
		cin >> n >> m; 

		int start, end;
		float cost;

		for (int i = 0; i < m; i++)
		{
			cin >> start >> end >> cost;
			adj[start].push_back(make_pair(end, cost));
		}

		vector<float> dist = dijkstra(n, 0);

		cout.precision(10);
		cout << fixed << dist[n - 1] << endl;
	}
}

vector<float> dijkstra(int v, int src)
{
	vector<float> dist(v, INF);
	dist[src] = 1;
	priority_queue<pair<float, int>> pq;
	pq.push(make_pair(-1, src));

	while (!pq.empty())
	{
		float cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); i++)
		{
			int there = adj[here][i].first;
			float nextCost = cost * adj[here][i].second;

			cout << "here: " << here << " / there: " << there 
				<< " / here cost: " << cost << " / there cost: " << nextCost << endl;

			if (dist[there] > nextCost)
			{
				pq.push(make_pair(-nextCost, there));
				dist[there] = nextCost;
			}
		}

	}

	return dist;
}