#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int append(int here, int edge, int mod);
string gifts(vector<int> digits, int n, int m);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin.ignore();

		int allowedDigits, n, m;

		cin >> allowedDigits >> n >> m;

		vector<int> digits;

		while (allowedDigits != 0)
		{
			digits.push_back(allowedDigits % 10);
			allowedDigits /= 10;
		}

		string result = gifts(digits, n, m);

		cout << result << endl;
	}
}

int append(int here, int edge, int mod)
{
	int there = here * 10 + edge;
	return there >= mod ? mod + there % mod : there % mod;
}

string gifts(vector<int> digits, int n, int m)
{
	sort(digits.begin(), digits.end());

	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;

	parent[0] = 0;
	q.push(0);

	while (!q.empty())
	{
		int here = q.front();
		q.pop();

		for (int i = 0; i < digits.size(); i++)
		{
			int there = append(here, digits[i], n);
			if (parent[there] == -1)
			{
				parent[there] = here;
				choice[there] = digits[i];
				q.push(there);
			}
		}
	}

	if (parent[n + m] == -1) return "IMPOSSIBLE";

	string resultC;
	int here = n + m;
	while (parent[here] != here)
	{
		resultC += char('0' + choice[here]);
		here = parent[here];
	}

	reverse(resultC.begin(), resultC.end());

	return resultC;
}