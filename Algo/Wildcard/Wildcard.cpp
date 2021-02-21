#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;
const int MAX_TEXT_LENGTH = 100;
char input[MAX_BUFFER_SIZE];

string src, dest;
int cache[MAX_TEXT_LENGTH][MAX_TEXT_LENGTH] = {-1, };
vector<string> results;

bool IsMatched(int srcIdx, int destIdx);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	cin.ignore();
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// initialize
		src = "";

		// input
		cin.getline(input, MAX_BUFFER_SIZE);
		src = string(input);

		int itemNum = 0;
		cin >> itemNum;

		cin.ignore();
		for (int i = 0; i < itemNum; i++)
		{
			cin.getline(input, MAX_BUFFER_SIZE);
			dest = string(input);

			// initialize
			for (int i = 0; i < MAX_TEXT_LENGTH; i++)
				for (int j = 0; j < MAX_TEXT_LENGTH; j++)
					cache[i][j] = -1;

			if (IsMatched(0, 0) == 1)
			{
				results.push_back(dest);
			}
		}
	}

	sort(results.begin(), results.end(), greater<string>());
	for (auto result : results)
	{
		cout << result << endl;
	}

	_getch();
}

bool IsMatched(int srcIdx, int destIdx)
{
	int& ret = cache[srcIdx][destIdx];
	if (ret != -1) return ret;

	ret = 0;

	if (srcIdx < src.length() && destIdx < dest.length() &&
		(src[srcIdx] == '?' || src[srcIdx] == dest[destIdx]))
		ret = IsMatched(srcIdx + 1, destIdx + 1);
	if (srcIdx == src.length()) ret = (destIdx == dest.length() ? 1 : 0);
	if (src[srcIdx] == '*')
	{
		if (IsMatched(srcIdx + 1, destIdx) == 1 ||
			(destIdx < dest.length() && IsMatched(srcIdx, destIdx + 1) == 1))
			ret = 1;
	}

	return ret;
}