#include <iostream>

using namespace std;

const int MAX_N = 101;
const int MOD = 10000000;

int cache[MAX_N][MAX_N];

int n;

int getTotPoly(int n);
int poly(int n, int top);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> n;

		// Initialize
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cache[i][j] = -1;

		// Process
		cout << getTotPoly(n) << endl;
	}
}

int getTotPoly(int n)
{
	int ret = 0;

	for (int top = 1; top <= n; top++)
		ret = (ret + poly(n, top)) % MOD;
	
	return ret;
}

int poly(int n, int top)
{
	int& ret = cache[n][top];
	if (ret != -1) return ret;
	
	// Initialize !!
	ret = 0;

	if (n == top) return ret = 1;

	for (int i = 1; i <= n - top; i++)
		ret = (ret + poly(n - top, i) * (top + i - 1)) % MOD;

	return ret;
}