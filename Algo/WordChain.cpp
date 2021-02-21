#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool **adjMatrix;
bool *seen;
vector<vector<string>> seenWordsContainer;

void MakeGraph(vector<string> & const words);
void dfs(int here, unsigned int depth, vector<string> seenWords, vector<string> & const words);

int main()
{
	adjMatrix = nullptr;
	seen = nullptr;

	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int wordCnt = 0;
		cin >> wordCnt;
		cin.ignore();

		vector<string> words;

		for (int wIter = 0; wIter < wordCnt; wIter++)
		{
			string word;
			std::getline(std::cin, word);
			words.push_back(word);
		}

		MakeGraph(words);

		seen = new bool[words.size()]{ false, };

		for (int i = 0; i < words.size(); i++)
		{
			vector<string> seenWords;
			dfs(i, 0, seenWords, words);
		}

		if (seenWordsContainer.size() > 0)
		{
			for (int i = 0; i < seenWordsContainer.size(); i++)
			{
				for (int j = 0; j < seenWordsContainer[i].size(); j++)
				{
					cout << seenWordsContainer[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		else
		{
			cout << "IMPOSSIBLE" << endl;
		}

		for (int i = 0; i < words.size(); i++)
		{
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
		delete[] seen;

		seenWordsContainer.clear();
		words.clear();
	}
}

void MakeGraph(vector<string> & const words)
{
	int wordCnt = words.size();

	adjMatrix = new bool*[wordCnt];
	for (int i = 0; i < wordCnt; i++)
	{
		adjMatrix[i] = new bool[wordCnt] {false, };
	}

	for (int i = 0; i < wordCnt; i++)
	{
		for (int j = 0; j < wordCnt; j++)
		{
			if (i == j) continue;

			if (words[i][words[i].size() - 1] == words[j][0])
			{
				adjMatrix[i][j] = true;
			}
		}
	}
}

void dfs(int here, unsigned int depth, vector<string> seenWords, vector<string> & const words)
{
	seen[here] = true;
	seenWords.push_back(words[here]);

	for (int there = 0; there < words.size(); there++)
	{
		if (adjMatrix[here][there] && seen[there] == false)
		{
			dfs(there, depth + 1, seenWords, words);
		}
	}

	if (depth == words.size() - 1)
	{
		vector<string> tmpSeenWords;

		for (int i = 0; i < seenWords.size(); i++)
		{
			tmpSeenWords.push_back(seenWords[i]);
		}

		seenWordsContainer.push_back(tmpSeenWords);
	}
	else
	{
		// 만약 마지막 단어까지 dfs()가 호출되지 않은 경우,
		// 다른 dfs()를 수행하기 위해 현재 접근한 노드를 못 본 척한다.
		seen[here] = false; 
	}
}