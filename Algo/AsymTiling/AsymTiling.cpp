#include <iostream>

using namespace std;

const int MAX_N = 101;
const int MOD = 1000000007;

int n;
int cache[MAX_N];

int tiling(int n);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> n;

		// Initialize
		for (int i = 0; i <= n; i++) cache[i] = -1;

		// Process
		int fullTiled = tiling(n);
		int symmetricTiled = -1;

		if (n == 0 || n == 1 || n == 2) symmetricTiled = n;
		else if (n % 2 == 0) symmetricTiled = (tiling(n / 2) + tiling((n - 2) / 2)) % MOD;
		else symmetricTiled = tiling((n - 1) / 2);

		int ret = (fullTiled - symmetricTiled + MOD) % MOD;

		cout << ret << endl;
	}
}

int tiling(int tileNum)
{
	int& ret = cache[tileNum];
	if (ret != -1) return ret;

	if (tileNum == 0) return ret = 0;
	else if (tileNum == 1) return ret = 1;
	else if (tileNum == 2) return ret = 2;

	ret = (tiling(tileNum - 1) + tiling(tileNum - 2)) % MOD;

	return ret;
}
