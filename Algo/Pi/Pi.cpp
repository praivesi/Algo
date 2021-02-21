#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_BUFFER_SIZE = 10001;
const int MAX_INPUT_SIZE = 10001;
const int MAX_DIFFICULTY = 99999;

char input[MAX_BUFFER_SIZE];
int cache[MAX_INPUT_SIZE + 1];

int getMinDiff(int start);
int calcMinDiff(int start, int end);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	cin.ignore();
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin.getline(input, MAX_BUFFER_SIZE);

		// initialize
		for (int i = 0; i < MAX_INPUT_SIZE + 1; i++) cache[i] = MAX_DIFFICULTY;

		// to do
		cout << getMinDiff(0) << endl;
	}
}

int getMinDiff(int start)
{
	int& ret = cache[start];
	if (ret != MAX_DIFFICULTY) return ret;

	if (start == strlen(input)) return 0;
	if (strlen(input) - start < 3) return MAX_DIFFICULTY;

	for (int i = 2; i < 5; i++)
	{
		if (start + i >= strlen(input)) break;
		ret = min(ret, calcMinDiff(start, start + i) + getMinDiff(start + i + 1));
	}

	return ret;
}

int calcMinDiff(int start, int end)
{
	int i = 0;

	for (i = start; i < end; i++)
		if (input[i] != input[i + 1]) break;
	if (i == end) return 1;

	for (i = start; i < end; i++)
		if (input[i] + 1 != input[i + 1]) break;
	if (i == end) return 2;

	for (i = start; i < end; i++)
		if (input[i] - 1 != input[i + 1]) break;
	if (i == end) return 2;

	switch (end - start)
	{
	case 2:
		if (input[start] == input[start + 2]) return 4;
	case 3:
		if (input[start] == input[start + 2] &&
			input[start + 1] == input[start + 3]) return 4;
	case 4:
		if (input[start] == input[start + 2] == input[start + 4] &&
			input[start + 1] == input[start + 3]) return 4;
	}

	for (i = start; i < end - 1; i++)
		if (input[start + 2] - input[start + 1] != input[start + 1] - input[start]) break;
	if (i == end - 1) return 5;

	return 10;
}