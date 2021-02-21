#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <conio.h>

using namespace std;

const int MAX_CNT = 101;
const long long NEGINF = numeric_limits<long long>::min();

vector<int> first, second, join;
int firstCnt = 0, secondCnt = 0;
long long cache[MAX_CNT][MAX_CNT];

long long jLis(int n, int m);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int num = 0;

		cin >> firstCnt >> secondCnt;

		// Initialize
		first.clear(); second.clear(); join.clear();
		for (int i = 0; i < firstCnt; i++)
			for (int j = 0; j < secondCnt; j++)
				cache[i][j] = -1;

		// Insert input
		for (int i = 0; i < firstCnt; i++)
		{
			cin >> num;
			first.push_back(num);
		}
		for (int i = 0; i < secondCnt; i++)
		{
			cin >> num;
			second.push_back(num);
		}

		// Process
		cout << jLis(-1, -1) << endl;
	}

	_getch();
}

long long jLis(int n, int m)
{
	long long& ret = cache[n + 1][m + 1];
	if (ret != -1) return ret;

	ret = 2;
	long long fe = (n == -1 ? NEGINF : first[n]);
	long long se = (m == -1 ? NEGINF :  second[m]);

	long long maxe = max(fe, se);

	for (int nextF = n + 1; nextF < firstCnt; nextF++)
		if (maxe < first[nextF])
		{
			cout << "first : " << first[nextF] << " ";
			ret = max(ret, jLis(nextF, m) + 1);
			cout << " / ret : " << ret << endl;
		}

	cout << endl;

	for (int nextS = m + 1; nextS < secondCnt; nextS++)
		if (maxe < second[nextS])
		{
			cout << "second : " << second[nextS];
			ret = max(ret, jLis(n, nextS) + 1);
			cout << " / ret : " << ret << endl;
		}

	/*
	cout << "ret >> " << ret << endl << "FIRST >> ";
	for (int i = 0; i < n; i++) cout << first[i] << " ";
	cout << endl << "SECOND >> ";
	for (int i = 0; i < m; i++) cout << second[i] << " ";
	cout << endl;
	*/

	return ret;
}