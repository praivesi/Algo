#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

typedef struct pillar {
	double y;
	double x;
	double r;
} pillar;

vector<pillar> pillars;

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int n = 0;
	double y = 0, x = 0, r = 0;
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Initialize
		pillars.clear();

		// Input
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> y >> x >> r;
			pillars.push_back(pillar{y, x, r});
		}

		// Process

		// Output
		
	}

	_getch();
}