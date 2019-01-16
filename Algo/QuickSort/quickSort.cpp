#include <iostream>
#include <vector>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;

void quick(vector<int> &items, int start, int end);
void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0, elemNum = 0;
	char inputBuffer[MAX_BUFFER_SIZE];
	vector<int> items;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> elemNum;
		cin.ignore();

		items.clear();

		cin.getline(inputBuffer, MAX_BUFFER_SIZE);
		splitStringWithDelim(inputBuffer, items, ' ', MAX_BUFFER_SIZE);

		quick(items, 0, items.size() - 1);

		for (auto &e : items)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}

void quick(vector<int> &items, int start, int end)
{
	if (start >= end) return; // element count is one
	if (end - start == 1) // element cout is two
	{
		if (items[start] > items[end]) swap(items[start], items[end]);
		return;
	}

 	int pivot = start, low = start + 1, high = end;

	while (high > low)
	{
		if (items[low] > items[pivot] && items[high] <= items[pivot]) swap(items[low], items[high]);
		while (low <= end && items[low] <= items[pivot]) low++;
		while (high >= start + 1 && items[high] > items[pivot]) high--;
	}
	swap(items[pivot], items[high]);

	quick(items, start, high - 1);
	quick(items, high + 1, end);
}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize)
{
	char *buf = new char[256]();
	int sourceIdx = 0;
	int bufIdx = 0;

	for (sourceIdx = 0; sourceIdx < maxSize; sourceIdx++)
	{
		if (source[sourceIdx] == delim || source[sourceIdx] == '\0')
		{
			// copy buffered string to result array
			buf[bufIdx] = '\0';
			result.push_back(atoi(buf));

			// if source string is end, break for loop
			if (source[sourceIdx] == '\0') break;

			bufIdx = 0;
		}
		else
		{
			buf[bufIdx] = source[sourceIdx];
			bufIdx++;
		}
	}

	return;
}