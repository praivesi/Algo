#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> m, e;
vector<pair<int, int>> lunchSet;

int minLunchTime();

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int n, mInput = 0, eInput = 0;
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Initialize
		m.clear();
		e.clear();
		lunchSet.clear();

		// Input
		cin >> n;

		for (int i = 0; i < n; i++)
		{
			cin >> mInput;
			m.push_back(mInput);
		}

		for (int i = 0; i < n; i++)
		{
			cin >> eInput;
			e.push_back(eInput);
		}

		// Process
		for (int i = 0; i < n; i++)
			lunchSet.push_back(make_pair(-e[i], m[i]));

		int totTime = minLunchTime();

		// Output
		cout << totTime << endl;
	}
}

int minLunchTime()
{
	int bakedTime = 0, totalTime = 0;
	sort(lunchSet.begin(), lunchSet.end());

	for (auto &lunch : lunchSet)
	{
		bakedTime += -lunch.first;
		totalTime = max(totalTime, bakedTime + lunch.second);
	}

	return totalTime;
}