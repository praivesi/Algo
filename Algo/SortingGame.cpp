#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int bfs(vector<int>& perm);

int main()
{
	int caseNum;
	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int n;
		cin >> n;

		vector<int> items;

		int input_item;
		for (int nIter = 0; nIter < n; nIter++)
		{
			cin >> input_item;
			items.push_back(input_item);
		}

		int shortest_distance = bfs(items);

		cout << shortest_distance << endl;
	}
}

int bfs(vector<int>& perm) 
{
	int n = perm.size();

	vector<int> sorted = perm;
	sort(perm.begin(), perm.end());

	queue<vector<int>> q;
	map<vector<int>, int> distance;

	distance[perm] = 0;
	q.push(perm);

	while (!q.empty())
	{
		vector<int> here = q.front();
		q.pop();

		if (here == sorted) return distance[here];
		int cost = distance[here];

		for (int i = 0; i < n; i++)
		{
			for (int j = i + 2; j <= n; j++)
			{
				reverse(here.begin() + i, here.begin() + j);
				
				if (distance.count(here) == 0)
				{
					distance[here] = cost + 1;
					q.push(here);
				}
				
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}

	return -1;
}