#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

const int MAX_N = 50;
const int MAX_P = 1000000000 + 100;
const int MAX_L = 50;

int n, p, l;
int cache [MAX_N];

int lengthAtGen(string seed, int gen);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input
		cin >> n >> p >> l;

		// Initialize
		for (int i = 0; i < n; i++)
			cache[i] = -1;

		// Process
		lengthAtGen("FX", n);

		// Output
		for (int i = 0; i < n; i++)
			cout << cache[i] << " ";
		cout << endl;
	}

	_getch();
}

int lengthAtGen(string seed, int gen)
{
	int &ret = cache[gen];

	if (gen == 0) return ret = seed.length();

	if (ret != -1) return ret;
	ret = 0;


	for (int i = 0; i < seed.length(); i++)
	{
		if (seed[i] == 'X')
			ret += lengthAtGen("X+YF", gen - 1);
		else if (seed[i] == 'Y')
			ret += lengthAtGen("FX-Y", gen - 1);
		else
			ret += 1;
	}


}
