#include <iostream>
#include <ctime>

using namespace std;

const int GEN_CNT = 6;

int main()
{
	srand((unsigned int)time(0));

	cout << GEN_CNT / 2 << endl;
	for (int i = 0; i < GEN_CNT; i++)
	{
		int numberSize = 0;

		if (i / 2 == 0) numberSize = 1000;
		else if (i / 2 == 1) numberSize = 10000;
		else if (i / 2 == 2) numberSize = 100000;
		else numberSize = 1000;

		for (int n = 0; n < numberSize; n++)
		{
			if (n == 0) cout << rand() % 10 + 1;
			else cout << rand() % 10;
		}
		cout << endl;
	}
}