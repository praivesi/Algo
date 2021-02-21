#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_STUFF_NUM = 100;
const int MAX_CARRIER_CAPACITY = 1001;
const int MAX_STUFF_NAME_LENGHT = 20;
const int MAX_STUFF_VOLUME = 1001;
const int MAX_STUFF_DESIRE = 1001;

int C = 0, N = 0, W = 0;

typedef struct stuff {
	string name = "";
	int volume = 0;
	int desire = 0;
} stuff;

stuff *stuffList = NULL;
vector<stuff> picked;
int cache[MAX_STUFF_NUM][MAX_CARRIER_CAPACITY];

int pack(int stuffIdx, int capacity);
void reconstruct(int stuffIdx, int capacity);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input & Initialize
		cin >> N >> W;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < W + 1; j++)
				cache[i][j] = -1;

		stuffList = new stuff[N];
		for (int i = 0; i < N; i++)
			cin >> stuffList[i].name >> stuffList[i].volume >> stuffList[i].desire;

		picked.clear();

		// Process
		int ret = pack(0, W);
		reconstruct(0, W);

		cout << ret << " " << picked.size() << endl;
		for (auto &p : picked)
		{
			cout << p.name << endl;
		}

		// Dispose
		delete[] stuffList;
	}
}

int pack(int stuffIdx, int capacity)
{
	if (stuffIdx == N) return 0;

	int &ret = cache[stuffIdx][capacity];
	if (ret != -1) return ret;

	ret = pack(stuffIdx + 1, capacity);

	if (capacity >= stuffList[stuffIdx].volume)
		ret = max(ret, pack(stuffIdx + 1, capacity - stuffList[stuffIdx].volume) + stuffList[stuffIdx].desire);

	return ret;
}

void reconstruct(int stuffIdx, int capacity)
{
	if (stuffIdx == N) return;

	if(cache[stuffIdx][capacity] == cache[stuffIdx + 1][capacity])
		reconstruct(stuffIdx + 1, capacity);
	else
	{
		picked.push_back(stuffList[stuffIdx]);
		reconstruct(stuffIdx + 1, capacity - stuffList[stuffIdx].volume);
	}
}