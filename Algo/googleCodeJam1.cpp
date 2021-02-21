#include <iostream>
#include <cmath>

using namespace std;

int n, a, b;

void split();

int main()
{
	int caseNum;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input
		cin >> n;

		// Initialize
		a = 0; b = 0;

		// Process
		split();

		// Output
		cout << "Case #" << (cIter + 1) <<  ": " << a << " " << b << endl << flush;
	}
}

void split()
{
	int pos = 0;
	int tmpN = n;

	while (tmpN != 0)
	{
		pos++;
		tmpN /= 10;
	}

	a = n;
	while (pos != 0)
	{
		int div = pow(10, pos - 1);
		int aPos = a % (int)pow(10, pos);
		aPos /= div;

		if (aPos == 0)
		{
			pos--;
			continue;
		}
		else if (aPos == 5)
		{
			a -= 2 * pow(10, pos - 1);
			b += 2 * pow(10, pos - 1);
		}
		else
		{
			a -= pow(10, pos - 1);
			b += pow(10, pos - 1);
		}

		pos--;
	}
}
