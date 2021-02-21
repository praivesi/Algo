#include <iostream>
#include <list>
#include <conio.h>

using namespace std;

int n = 0, k = 0;

void josephus(list<int> &survivors);

int main()
{
	int caseNum = 0;
	cin >> caseNum;
	
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input
		cin >> n >> k;

		// Initalize
		list<int> survivors;
		for (int i = 1; i <= n; i++)
			survivors.push_back(i);

		// Process
		josephus(survivors);

		// Output
		for (auto s : survivors)
			cout << s << " ";
		cout << endl;
	}

	_getch();
}

void josephus(list<int> &survivors)
{
	auto kill = survivors.begin();

	while (n > 2)
	{
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();

		n--;
		
		for (int i = 0; i < k - 1; i++)
		{
			kill++;
			if (kill == survivors.end()) kill = survivors.begin();
		}
	}
}