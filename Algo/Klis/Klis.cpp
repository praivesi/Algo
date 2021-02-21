#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 500;
const int MAX_K = 2000000000 + 100;

int N = 0, K = 0;
vector<int> nums, kLis;
int cacheLen[MAX_N + 1];
int cacheCnt[MAX_N + 1];

int lisLength(int start);
int lisCount(int start);
void reconstruct(int start, int skip);

int main()
{
	int caseNum;

	cin >> caseNum;
	
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Read inputs
		cin >> N >> K;

		// Initialize
		nums.clear();
		kLis.clear();

		for (int i = 0; i < MAX_N; i++)
		{
			cacheLen[i] = -1;
			cacheCnt[i] = -1;
		}

		int buf = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> buf;
			nums.push_back(buf);
		}

		// Process
		lisLength(-1);
		lisCount(-1);
		reconstruct(-1, K - 1);

		// Output
		cout << "[ CASE " << cIter + 1 << " ]" << endl;
		cout << "( LIS Length ) ";
		for (int i = 0; i < N + 1; i++)
			cout << cacheLen[i] << " ";
		cout << endl;

		cout << "( LIS Count ) ";
		for (int i = 0; i < N + 1; i++)
			cout << cacheCnt[i] << " ";
		cout << endl;

		cout << "( KLIS members ) ";
		for (auto k : kLis)
		{
			cout << k << " ";
		}
		cout << endl << endl;
	}
}

// Get LIS length from nums[start]
int lisLength(int start)
{
	int &ret = cacheLen[start + 1];

	if (start == N - 1) return ret = 1;
	if (ret != -1) return ret;

	ret = 1;

	for (int next = start + 1; next < N; next++)
		if (start == -1 || nums[start] < nums[next])
			ret = max(ret, lisLength(next) + 1);

	return ret;
}

// Get LIS count from nums[start]
int lisCount(int start)
{
	int &ret = cacheCnt[start + 1];

	if (lisLength(start) == 1) return ret = 1;
	if (ret != -1) return ret;
	ret = 0;

	for (int next = start + 1; next < N; next++)
		if ((start == -1 || nums[start] < nums[next]) && lisLength(start) == lisLength(next) + 1)
			ret = min(ret + lisCount(next), MAX_K);

	return ret;
}

// Get K th LIS
void reconstruct(int start, int skip)
{
	if (start != -1) kLis.push_back(nums[start]);

	vector<pair<int, int>> followers;

	for (int next = start + 1; next < N; next++)
		if ((start == -1 || nums[start] < nums[next]) && lisLength(start) == lisLength(next) + 1)
			followers.push_back(make_pair(nums[next], next));
	sort(followers.begin(), followers.end());

	for (int i = 0; i < followers.size(); i++)
	{
		int idx = followers[i].second;
		int cnt = lisCount(idx);
		if (cnt <= skip)
		{
			skip -= cnt;
		}
		else
		{
			reconstruct(idx, skip);
			break;
		}
	}

}