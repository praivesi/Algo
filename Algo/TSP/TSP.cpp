#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;
const int MAX_TOWN_NUM = 8;

vector<vector<double>> dist;
bool visited[MAX_TOWN_NUM];

int townNum = 0;

double getMinDistance(int curTown);
void splitStringWithDelim(char* source, vector<double> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0;
	char buffer[MAX_BUFFER_SIZE] = {0, };

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> townNum;
		cin.ignore();
		
		dist.clear();
		for (int v = 0; v < townNum; v++)
		{
			visited[v] = false;
		}
		for (int y = 0; y < townNum; y++)
		{
			vector<double> row;

			cin.getline(buffer, MAX_BUFFER_SIZE);
			
			splitStringWithDelim(buffer, row, ' ', MAX_BUFFER_SIZE);
			dist.push_back(row);
		}

		double min = 99999, ret = 0;
		for (int i = 0; i < townNum; i++)
		{
			for (int j = 0; j < townNum; j++) visited[j] = false;

			ret = getMinDistance(i);
			if (min > ret) min = ret;
		}

		cout << setprecision(10) << fixed << ret << endl;
	}
}

double getMinDistance(int curTown)
{
	double minDist = 99999, curDist = 0;
	visited[curTown] = true;

	for (int v = 0; v < townNum; v++)
	{
		if (visited[v] == false) break;
		if (v == townNum - 1)
		{
			return 0;
		}
	}


	for (int i = 0; i < townNum; i++)
	{
		if (visited[i]) continue;

		curDist = getMinDistance(i) + dist[curTown][i];
		visited[i] = false;
		if (minDist > curDist)
		{
			minDist = curDist;
		}
	}

	return minDist;
}

void splitStringWithDelim(char* source, vector<double> &result, char delim, int maxSize)
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

			result.push_back(atof(buf));

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