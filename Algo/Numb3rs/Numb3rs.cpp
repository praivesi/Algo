#include <iostream>
#include <iomanip>

using namespace std;

int N = 0, D = 0, P = 0;
int **linked = NULL;
double **nextPos = NULL;
int T = 0;
int *Q = NULL;

double *curTownPos = NULL;

void calcNextPos();
void findDunibal(int startTown, int day);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> N >> D >> P;

		linked = new int*[N];
		nextPos = new double*[N];

		for (int i = 0; i < N; i++)
		{
			linked[i] = new int[N];
			nextPos[i] = new double[N];
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> linked[i][j];

		cin >> T;
		Q = new int[T];
		for (int i = 0; i < T; i++)
		{
			cin >> Q[i];
		}

		// Process
		calcNextPos();
		findDunibal(P, D);

		for (int i = 0; i < T; i++)
			cout << setprecision(8) << fixed << curTownPos[Q[i]] << " ";
		cout << endl;

		// Dispose
		for (int i = 0; i < N; i++)
			delete[] linked[i];
		delete[] linked;

		delete[] Q;
	}
}

void findDunibal(int startTown, int day)
{
	curTownPos = new double[N];
	for (int i = 0; i < N; i++)
	{
		if (i != startTown) curTownPos[i] = 0;
		else curTownPos[i] = 1;
	}

	double *nextTownPos = new double[N] {0, };

	for (int d = 0; d < day; d++)
	{
		for (int i = 0; i < N; i++)
			nextTownPos[i] = 0;

		// Calculate case of one day pass
		for (int t = 0; t < N; t++)
		{
			for (int next = 0; next < N; next++)
			{
				if (next == t) continue;
				nextTownPos[next] += curTownPos[t] * nextPos[t][next];
			}
		}

		for (int t = 0; t < N; t++)
			curTownPos[t] = nextTownPos[t];
	}
}

void calcNextPos()
{
	double linkCnt = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			if (linked[i][j] == 1) linkCnt++;

		if (linkCnt == 0) continue;

		for (int j = 0; j < N; j++)
			nextPos[i][j] = linked[i][j] / linkCnt;

		linkCnt = 0;
	}
}