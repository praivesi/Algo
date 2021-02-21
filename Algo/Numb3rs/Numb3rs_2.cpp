#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_TOWN_NUM = 50;
const int MAX_DAY_NUM = 100;
double cache[MAX_TOWN_NUM][MAX_DAY_NUM];

int N = 0, D = 0, P = 0;
int **linked = NULL;
int T = 0;
int *Q = NULL;
int subQ = 0;
int degree[MAX_TOWN_NUM];

double search(int here, int days);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		for (int i = 0; i < MAX_TOWN_NUM; i++)
			for (int j = 0; j < MAX_DAY_NUM; j++)
				cache[i][j] = -1.0;

		cin >> N >> D >> P;

		linked = new int*[N];

		for (int i = 0; i < N; i++)
		{
			linked[i] = new int[N];
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

		int degCount = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				if (linked[i][j] == 1) degCount++;
			degree[i] = degCount;
			degCount = 0;
		}

		// Process
		for (int i = 0; i < T; i++)
		{
			subQ = Q[i];
			cout << setprecision(8) << fixed << search(subQ, D) << " ";
		}
		cout << endl;

		// Dispose
		for (int i = 0; i < N; i++)
			delete[] linked[i];
		delete[] linked;

		delete[] Q;
	}
}

double search(int here, int days)
{
	if (days == 0) return (here == P) ? 1.0 : 0.0;

	double &ret = cache[here][days];
	if (ret != -1) return ret;

	ret = 0.0;

	for (int there = 0; there < N; there++)
		if (linked[here][there] == 1) ret += search(there, days - 1) / degree[there];

	return ret;

}