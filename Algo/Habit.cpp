#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getMostHabit(string &habit, int minLength);
int getCommonPrefixLength(string &s, int startIdx, int endIdx);
vector<int> getSuffixArray(string &habit);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int k = 0;
	string habit = "";

	for (int i = 0; i < caseNum; i++)
	{
		cin >> k;
		cin.ignore();

		std::getline(std::cin, habit);

		// Process
		int most = getMostHabit(habit, k);

		cout << most << endl;
	}
}

typedef struct Comparator {
	vector<int> group;
	int t;

	Comparator(vector<int> _group, int _t) {
		group = _group;
		t = _t;
	}

	bool operator() (int a, int b) {
		if (group[a] != group[b])  return group[a] < group[b];
		else return group[a + t] < group[b + t];
	}

}Comparator;

int getMostHabit(string &habit, int minLength)
{
	vector<int> suffixArray = getSuffixArray(habit);

	int n = habit.size();

	int ret = 0;
	for (int i = 0; i < n - minLength; i++)
		ret = max(ret, getCommonPrefixLength(habit, suffixArray[i], suffixArray[i + minLength - 1]));

	return ret;
}

int getCommonPrefixLength(string &s, int startIdx, int endIdx)
{
	int i = startIdx, j = endIdx, k = 0;
	int n = s.size();

	while (i < n && j < n && s[i] == s[j]) { i++; j++; k++; }

	return k;
}

vector<int> getSuffixArray(string &habit)
{
	int n = habit.size();

	int t = 1;
	vector<int> group(n + 1);
	group[n] = -1;

	vector<int> perm(n);

	for (int i = 0; i < n; i++)
	{
		group[i] = habit[i];
		perm[i] = i;
	}

	while (t < n)
	{
		Comparator compareUsingT2(group, t);

		sort(perm.begin(), perm.end(), compareUsingT2);

		/*cout << "						[ PERMISSION START ]						" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "(group # " << group[perm[i]] << ") " << habit.substr(perm[i]) << endl;
		}
		cout << "						[ PERMISSION END ]							" << endl;
		cout << endl;*/

		vector<int> new_group(n + 1);
		new_group[n] = -1;
		new_group[perm[0]] = 0;

		t *= 2;
		if (t >= n) break;

		for (int i = 1; i < n; i++)
		{
			if (compareUsingT2(perm[i - 1], perm[i]))
			{
				new_group[perm[i]] = new_group[perm[i - 1]] + 1;
			}
			else
			{
				new_group[perm[i]] = new_group[perm[i - 1]];
			}
		}

		group = new_group;
	}

	return perm;
}
