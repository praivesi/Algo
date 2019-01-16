#include <iostream>
#include <vector>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;

vector<int> items;

vector<int> sort(int start, int end);
vector<int> merge(vector<int> &first, vector<int> &second);
void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0, itemNum = 0;
	char inputBuffer[MAX_BUFFER_SIZE];

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> itemNum;
		cin.ignore();

		memset(inputBuffer, 0, MAX_BUFFER_SIZE);
		items.clear();

		cin.getline(inputBuffer, MAX_BUFFER_SIZE);
		splitStringWithDelim(inputBuffer, items, ' ', MAX_BUFFER_SIZE);

		vector<int> res = sort(0, items.size());

		for (auto &e : res)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}

vector<int> sort(int start, int end)
{
	if (start == end)
	{
		vector<int> init;
		if (start == items.size())
		{
			init.push_back(items[start - 1]);
		}
		else
		{
			init.push_back(items[start]);
		}
		return init;
	}

	int mid = (start + end) / 2;

	vector<int> first = sort(start, mid);
	vector<int> second = sort(mid + 1, end);

	return merge(first, second);
}

vector<int> merge(vector<int> &first, vector<int> &second)
{
	int fx = 0, sx = 0;
	vector<int> merged;

	for (fx = 0; fx < first.size(); fx++)
	{
		if (first[fx] > second[sx])
		{
			merged.push_back(second[sx]);
			if (++sx == second.size()) break;
			fx--;
		}
		else
		{
			merged.push_back(first[fx]);
		}
	}

	if (fx != first.size()) while (fx != first.size()) merged.push_back(first[fx++]);
	else if (sx != second.size()) while (sx != second.size()) merged.push_back(second[sx++]);
	else cout << "What the wrong happend !!" << endl;

	return merged;
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


