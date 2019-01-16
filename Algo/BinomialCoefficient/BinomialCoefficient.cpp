#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NUM = 1024;

int cache[MAX_NUM][MAX_NUM];

void initCache();
int binomial(int n, int r);

int main()
{
	int caseNum = 0;
	int n = 0, r = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		n = r = 0;
		initCache();

		cin >> n >> r;

		cout << binomial(n, r) << endl;
	}
}

void initCache()
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		for (int j = 0; j < MAX_NUM; j++)
		{
			cache[i][j] = -1;
		}
	}
}

int binomial(int n, int r)
{
	if (r == 0 && n == r) return 1;
	if (cache[n][r] != -1) return cache[n][r];
	cache[n][r] = binomial(n - 1, r - 1) + binomial(n - 1, r);

	return cache[n][r];
}