#include <iostream>

using namespace std;

int getHugCnt(int start, int end);
int getCenterHugCnt(int start, int end, int headPersonStart, int headPersonEnd);
bool IsAllHugged(int headPersonIdx);

const int MAX_PEOPLE_SIZE = 200001;

char inputBuffer[MAX_PEOPLE_SIZE];
char member[MAX_PEOPLE_SIZE];
char fan[MAX_PEOPLE_SIZE];

int main()
{
	int caseNum = 0;

	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin.getline(inputBuffer, MAX_PEOPLE_SIZE);
		strncpy_s(member, inputBuffer, strlen(inputBuffer) + 1);

		cin.getline(inputBuffer, MAX_PEOPLE_SIZE);
		strncpy_s(fan, inputBuffer, strlen(inputBuffer) + 1);

		int result = getHugCnt(0, strlen(fan) - 1);

		cout << result << endl;

		memset(member, 0, sizeof(member));
		memset(fan, 0, sizeof(fan));
	}
}

int getHugCnt(int start, int end)
{
	int memberCnt = strlen(member);

	if (end - start + 1 < memberCnt) return 0;

	int mid = (start + end) / 2;
	
	int leftHugCnt = getHugCnt(start, mid);
	int rightHugCnt = getHugCnt(mid + 1, end);
	int centerHugCnt = getCenterHugCnt(start, end, mid - memberCnt + 2, mid);

	return leftHugCnt + rightHugCnt + centerHugCnt;
}

int getCenterHugCnt(int start, int end, int headPersonStart, int headPersonEnd)
{
	int hugCnt = 0;
	int memberCnt = strlen(member);

	for (int i = headPersonStart; i <= headPersonEnd; i++)
	{
		if (i < start) continue;
		if (i + memberCnt > end + 1) break;
		if (IsAllHugged(i)) hugCnt++;
	}

	return hugCnt;
}

bool IsAllHugged(int headPersonIdx)
{
	for (int i = 0; i < strlen(member); i++)
	{
		if (member[i] == 'M' && fan[headPersonIdx + i] == 'M') return false;
	}

	return true;
}