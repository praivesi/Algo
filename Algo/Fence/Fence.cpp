#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;
vector<int> fenceHeights;

int getMaxArea(int start, int end);
int getCenterMax(int start, int end, int mid);
void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0, elNum = 0;
	char inputBuffer[MAX_BUFFER_SIZE];

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		fenceHeights.clear();

		cin >> elNum;
		cin.ignore();

		cin.getline(inputBuffer, MAX_BUFFER_SIZE);

		splitStringWithDelim(inputBuffer, fenceHeights, ' ', MAX_BUFFER_SIZE);

		int ret = getMaxArea(0, fenceHeights.size() - 1);

		cout << ret << endl;
	}
}

int getMaxArea(int start, int end)
{
	if (start == end) return fenceHeights[start];

	int mid = (start + end) / 2;

	int leftMax = getMaxArea(start, mid);
	int rightMax = getMaxArea(mid + 1, end);
	int centerMax = getCenterMax(start, end, mid);
	
	int ret = max(leftMax, rightMax);
	ret = max(ret, centerMax);

	return ret;
}

int getCenterMax(int start, int end, int mid)
{
	int low = mid, high = mid;
	int height = fenceHeights[mid];
	int area = fenceHeights[mid];

	while (start < low || high < end)
	{
		if (high < end && (low == start || fenceHeights[low - 1] < fenceHeights[high + 1]))
		{
			high++;

			height = min(height, fenceHeights[high]);
			area = max(area, height * (high - low + 1));
		}
		else
		{
			low--;
			
			height = min(height, fenceHeights[low]);
			area = max(area, height * (high - low + 1));
		}

		/*
		if (low == start)
		{
			if (high == end)
			{
				break;
			}
			else
			{
				high++;

				height = min(height, fenceHeights[high]);

				int nextArea = height * (high - low + 1);
				area = max(area, nextArea);
			}
		}
		else if(high == end)
		{
			low--;

			height = min(height, fenceHeights[low]);

			int nextArea = height * (high - low + 1);
			area = max(area, nextArea);
		}
		else
		{
			if (fenceHeights[low - 1] < fenceHeights[high + 1])
			{
				high++;

				height = min(height, fenceHeights[high]);

				int nextArea = height * (high - low + 1);
				area = max(area, nextArea);
			}
			else
			{
				low--;

				height = min(height, fenceHeights[low]);

				int nextArea = height * (high - low + 1);
				area = max(area, nextArea);
			}
		}
		*/
	}

	return area;
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