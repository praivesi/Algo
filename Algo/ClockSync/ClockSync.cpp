#include <iostream>
#include <vector>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;
const int SWITCH_NUM = 10;
const int CLOCK_NUM = 16;

const char* switches[10] = 
{
	{"oooxxxxxxxxxxxxx"},
	{"xxxoxxxoxoxoxxxx"},
	{"xxxxoxxxxxoxxxoo"},
	{"oxxxooooxxxxxxxx"},
	{"xxxxxxoooxoxoxxx"},
	{"oxoxxxxxxxxxxxoo"},
	{"xxxoxxxxxxxxxxoo"},
	{"xxxxooxoxxxxxxoo"},
	{"xoooooxxxxxxxxxx"},
	{"xxxoooxxxoxxxoxx"}
};
vector<int> clockState;
int pushed;

int getMinPush(int switchIdx);
void push(int switchIdx);
void unPushThreeTimes(int switchIdx);
bool IsSynced();
void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0;
	char inputBuffer[MAX_BUFFER_SIZE];

	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		clockState.clear();
		pushed = 0;

		cin.getline(inputBuffer, MAX_BUFFER_SIZE);
		splitStringWithDelim(inputBuffer, clockState, ' ', MAX_BUFFER_SIZE);

		cout << getMinPush(0) << endl;
	}
}

int getMinPush(int switchIdx)
{
	int minPushed = 99999, ret = 0;

	// push 0 ~ 3 times
	for (int i = 0; i < 4; i++)
	{
		if(i != 0) push(switchIdx); 
		if (IsSynced()) return pushed;
		if (switchIdx != SWITCH_NUM - 1)
		{
			ret = getMinPush(switchIdx + 1);
			if (minPushed > ret) minPushed = ret;
		}
	}

	// restore clcokState
	unPushThreeTimes(switchIdx);

	// IF there's no answer, return INF
	if (switchIdx == SWITCH_NUM - 1) return 999999;

	return minPushed;
}

void push(int switchIdx)
{
	for (int i = 0; i < CLOCK_NUM; i++)
	{
		if (switches[switchIdx][i] == 'o')
		{
			clockState[i] = (clockState[i] + 3) % 12;
		}
	}

	pushed++;
}

void unPushThreeTimes(int switchIdx)
{
	for (int i = 0; i < CLOCK_NUM; i++)
	{
		if (switches[switchIdx][i] == 'o')
		{
			clockState[i] = (clockState[i] + 3) % 12;
		}
	}

	pushed -= 3;
}

bool IsSynced()
{
	for (int i = 0; i < CLOCK_NUM; i++)
	{
		if (clockState[i] % 12 != 0) return false;
	}

	return true;
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