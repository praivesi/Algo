#include <iostream>
#include <bitset>
#include <algorithm>
#include <conio.h>

#define MAX_N 12
#define MAX_M 10

using namespace std;

int INF = 987654321;
int N, K, M, L;
int before[MAX_N][MAX_N];
int semesters[MAX_M][MAX_N];
int cache[10][1 << MAX_N];

unsigned int beforeBit[MAX_N];
unsigned int semBit[MAX_M];

int graduate(int semester, int taken);

int main()
{
	int caseNum;
	int beforeNum;
	int semNum;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> N >> K >> M >> L;

#pragma region Input
		for (int i = 0; i < N; i++)
		{
			beforeBit[i] = 0;

			cin >> beforeNum;
			if (beforeNum == 0)
			{
				beforeBit[i] = 0;
			}
			else
			{
				for (int j = 0; j < beforeNum; j++)
				{
					cin >> before[i][j];
					beforeBit[i] |= 1u << before[i][j];
				}
			}
		}

		for (int i = 0; i < M; i++)
		{
			semBit[i] = 0;

			cin >> semNum;
			if (semNum == 0)
			{
				semBit[i] = 0;
			}
			else
			{
				for (int j = 0; j < semNum; j++)
				{
					cin >> semesters[i][j];
					semBit[i] |= 1u << semesters[i][j];
				}
			}
		}
#pragma endregion

		// Initialize
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < (1 << MAX_N); j++)
				cache[i][j] = -1;

		// Process
		int minSem = graduate(0, 0);

		// Output
		if (minSem == INF) cout << "IMPOSSIBLE" << endl;
		else cout << minSem << endl;
	}

	_getch();
}

int graduate(int semester, int taken)
{
	if (bitset<32>(taken).count() >= K) return 0;

	if (semester == M) return INF;

	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;

	int canTake = (semBit[semester] & ~taken);

	for (int i = 0; i < N; i++)
		if ((canTake & (1 << i)) && (taken & beforeBit[i]) != beforeBit[i])
			canTake &= ~(1 << i);

	for (int take = canTake; take > 0; take = ((take - 1) & canTake))
	{
		if (bitset<32>(take).count() > L) continue;

		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}

	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}
