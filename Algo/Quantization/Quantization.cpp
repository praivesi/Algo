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
	// parts �� 1�̸� ������ quants ���� ��� �ϳ��� ����� �ǹǷ�
	// �ٷ� minError() �� ����Ͽ� �����Ѵ�.
	if (parts == 1) return minError(from, n - 1);

	// ��� quants �� �� ���Խ��״µ� parts �� �����ִٸ�
	// ���������� ����̹Ƿ� MAX_ERROR �� �����Ѵ�.
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

	// pSum �� double �� ĳ���� �ؾ� ��Ȯ�� ���� ���´�. 
	// ĳ���� ���ϸ� int / int ���� �Ҽ��� �ڸ��� ����ȴ�.
	// ĳ���� ������ �� �� ��° ���̽� ���� 653, 
	// ĳ���� ���� �� 651 �� ���Դ�. (�������� ��)
	int m = floor((double)pSum / (end - start + 1) + 0.5);

	return (end - start + 1) * m * m
			- 2 * m * pSum
			+ psqSum;
}