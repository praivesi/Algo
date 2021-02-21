#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

int n, p, l;

// '+' = true, '-' = false
vector<bool> sequence;

void getCurve(int gen, int max);
string generate();

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input
		cin >> n >> p >> l;

		// Initialize
		sequence.clear();

		// Process & Output
		sequence.push_back(true);
		getCurve(0, n);

		/*
		for (auto s : sequence)
			cout << s << " ";
		cout << endl;
		*/

		//cout << generate().substr(p - 1, l) << endl;
		cout << "n : " << n << " / p : " << p << " / l : " << l << " / generate() : " << generate() << endl;
	}

	_getch();
}

// gen - generation
void getCurve(int gen, int max)
{
	cout << "getCurve Entered .. gen is " << gen << endl;
	
	if (max == 0) return;
	else if (max == 1)
	{
		sequence.push_back(true);
		return;
	}
	if (gen > max) return;
	if (gen == 0) gen++;
	if (gen == 1)
	{
		sequence.push_back(true);
		gen++;
	}

	sequence.push_back(true);

	int revStart = sequence.size() / 2;
	for (int i = revStart; i >= 0; i--)
		sequence.push_back(!sequence[i]);

	getCurve(gen + 1, max);
}

string generate()
{
	string ret = "FX";
	bool fxIsLast = true;

	switch (sequence.size())
	{
	case 0:
		return ret;
	default :
		for (auto c : sequence)
		{
			ret += c ? "+" : "-";
			ret += fxIsLast ? "YF" : "FX";
			fxIsLast != fxIsLast;
		}
		return ret;
	}
}