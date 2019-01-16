#include <iostream>
#include <vector>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;

int studentCnt = 0, pairCnt = 0;
bool areFriend[10][10] = { false, };

int makePairing(bool done[10]);
void splitStringWithDelim(char* source, vector<int> &result, char delim, int maxSize);

int main()
{
	int caseNum = 0;
	char areFriendInput[MAX_BUFFER_SIZE];
	vector<int> areFriendInputParsed;
	bool done[10] = { false, };

	cin >> caseNum;
	
	for (int caseIter = 0; caseIter < caseNum; caseIter++)
	{
		/* Clear variables */
		for (auto &d : done)
		{
			d = false;
		}

		for (auto &fr : areFriend)
		{
			for (auto &f : fr)
			{
				f = false;
			}
		}

		areFriendInputParsed.clear();

		/* get input - studentCnt, relationShipResult */
		cin >> studentCnt >> pairCnt;
		cin.ignore();
		cin.getline(areFriendInput, MAX_BUFFER_SIZE);
		splitStringWithDelim(areFriendInput, areFriendInputParsed, ' ', MAX_BUFFER_SIZE);

		/* make friendShip array */
		for (int resultNum = 0; resultNum < areFriendInputParsed.size(); resultNum++)
		{
			if (resultNum % 2 == 1) continue;

			int studentElemFirst = areFriendInputParsed[resultNum];
			int studentElemSecond = areFriendInputParsed[resultNum + 1];

			areFriend[studentElemFirst][studentElemSecond] = true;
			areFriend[studentElemSecond][studentElemFirst] = true;
		}

		/* get result */
		cout << makePairing(done) << endl;
	}
}

int makePairing(bool done[10])
{
	int first = 0;
	for (first = 0; first < studentCnt; first++)
		if (done[first] == false) break;
	if (first == studentCnt) return 1;

	int ret = 0;
	for (int pair = first + 1; pair < studentCnt; pair++)
	{
		if (done[pair] == false && areFriend[first][pair])
		{
			done[first] = done[pair] = true;
			ret += makePairing(done);
			done[first] = done[pair] = false;
		}
	}

	return ret;
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

