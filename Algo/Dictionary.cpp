#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<bool>> adj;
vector<bool> visited;
vector<int> phase; // À§»ó

vector<string> words;

void makeGraph();
vector<int> topologicalSort();
void dfs(int here);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int i = 0; i < caseNum; i++)
	{
		int wordCnt = 0;
		cin >> wordCnt;
		cin.ignore();
		
		for (int j = 0; j < wordCnt; j++)
		{
			string word;
			std::getline(std::cin, word);
			words.push_back(word);
		}

		makeGraph();
		vector<int> ret = topologicalSort();

		if (ret.size() == 0)
		{
			cout << "INVALID HYPOTHESIS" << endl;
		}
		else
		{
			for (int i = 0; i < ret.size(); i++)
			{
				cout << (char)(ret[i] + 'a');
			}
			cout << endl;
		}

		words.clear();
	}
}

void makeGraph()
{
	adj = vector<vector<bool>>(26, vector<bool>(26, false));

	for (int j = 1; j < words.size(); j++)
	{
		int i = j - 1;
		int len = min(words[i].size(), words[j].size());
		for (int k = 0; k < len; k++)
		{
			if (words[i][k] != words[j][k])
			{
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = true;
				break;
			}
		}
	}
}

vector<int> topologicalSort()
{
	int n = adj.size();
	visited = vector<bool>(n, false);
	phase.clear();

	for (int i = 0; i < n; i++)
	{
		if (visited[i] == false) dfs(i);
	}

	reverse(phase.begin(), phase.end());

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (adj[phase[j]][phase[i]])
				return vector<int>();
		}
	}

	return phase;
}

void dfs(int here)
{
	//cout << "DFS visits " << here << endl;
	visited[here] = true;

	for (int there = 0; there < adj.size(); there++)
	{
		bool can_go_there = adj[here][there];

		if (can_go_there && visited[there] == false)
		{
			dfs(there);
		}
	}

	//phase.insert(phase.begin(), here);
	phase.push_back(here);
}
