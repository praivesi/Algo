#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

const unsigned int FIRST_SIGNAL = 1983;

int countK(unsigned int k, unsigned int n);

struct RNG {
	unsigned int seed;
	RNG() : seed(FIRST_SIGNAL) {}
	unsigned int next() {
		unsigned int ret = seed;
		seed = ((seed * 214013u + 2531011u));
		return ret % 10000 + 1;
	}
};

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	unsigned int k = 0, n = 0;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> k >> n;

		int count = countK(k, n);

		cout << count << endl;
	}
}

int countK(unsigned int k, unsigned int n)
{
	RNG rng;
	queue<unsigned int> signals;
	unsigned int rangeSum = 0, cnt = 0;

	for (unsigned int tail = 0; tail < n; tail++)
	{
		int newSignal = rng.next();
		rangeSum += newSignal;
		signals.push(newSignal);

		while (rangeSum > k)
		{
			rangeSum -= signals.front();
			signals.pop();
		}

		if (rangeSum == k) { cnt++; }
	}

	return cnt;
}
