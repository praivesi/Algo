#include <iostream>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>> lengths;

int getMinCopyTime();

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int n = 0, lengthInput = 0;
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Initialize
		lengths = priority_queue<int, vector<int>, greater<int>>();
		
		// Input
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> lengthInput;
			lengths.push(lengthInput);
		}

		// Process
		int minCopyTime = getMinCopyTime();

		// Output
		cout << minCopyTime << endl;
	
	}
}

int getMinCopyTime()
{
	int copyTime = 0, ret = 0;

	if (lengths.size() == 1)
		ret = lengths.top();

	while (lengths.size() > 1)
	{
		copyTime = lengths.top(); lengths.pop();
		copyTime += lengths.top(); lengths.pop();
		lengths.push(copyTime);
		ret += copyTime;
	}
	
	return ret;
}