#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_ERROR = 999999;
const int MAX_N = 100;
const int MAX_S = 10;

int cache[MAX_N][MAX_S];
int sum[MAX_N];
int sumSquare[MAX_N];

vector<int> quants;
int n = 0, s = 0;

int quantize(int from, int parts);
int minError(int start, int end);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> n >> s;
		
		// Initialize
		quants.clear();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < s; j++)
				cache[i][j] = MAX_ERROR;

		int input = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> input;
			quants.push_back(input);
		}

		sort(quants.begin(), quants.end());

		// Calculate
		sum[0] = quants[0];
		for (int i = 1; i < n; i++)
			sum[i] = sum[i - 1] + quants[i];

		sumSquare[0] = quants[0] * quants[0];
		for (int i = 1; i < n; i++)
			sumSquare[i] = sumSquare[i - 1] + quants[i] * quants[i];

		// Process
		cout << quantize(0, s) << endl;
	}
}

int quantize(int from, int parts)
{
	// parts 가 1이면 나머지 quants 들은 모두 하나로 묶어야 되므로
	// 바로 minError() 를 계산하여 리턴한다.
	if (parts == 1) return minError(from, n - 1);

	// 모든 quants 를 다 포함시켰는데 parts 가 남아있다면
	// 비정상적인 경우이므로 MAX_ERROR 를 리턴한다.
	if (from == n - 1 && parts > 1) return MAX_ERROR;

	int& ret = cache[from][parts - 1];
	if (ret != MAX_ERROR) return ret;

	for (int i = from + 1; i < n; i++)
		ret = min(ret, minError(from, i - 1) + quantize(i, parts - 1));

	return ret;
}

int minError(int start, int end)
{
	int pSum = sum[end] - (start == 0 ? 0 : sum[start - 1]);
	int psqSum = sumSquare[end] - (start == 0 ? 0 : sumSquare[start - 1]);

	// pSum 을 double 로 캐스팅 해야 정확한 값이 나온다. 
	// 캐스팅 안하면 int / int 여서 소수점 자리가 절삭된다.
	// 캐스팅 안했을 땐 두 번째 케이스 값이 653, 
	// 캐스팅 했을 땐 651 로 나왔다. (정상적인 값)
	int m = floor((double)pSum / (end - start + 1) + 0.5);

	return (end - start + 1) * m * m
			- 2 * m * pSum
			+ psqSum;
}