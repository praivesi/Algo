#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getMaxDup(const string &first, const string &second);
vector<int> getPartialMatch(const string &target);

int main()
{
	int caseNum = 0;
	int n = 0, result = 0;
	string first = "", second = "";

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin >> n;
		cin.ignore();

		std::getline(std::cin, first);

		result = 0;

		for (int spin = 0; spin < n; spin++)
		{
			std::getline(std::cin, second);

			// Process
			result += spin % 2 == 0 ? getMaxDup(first, second) : getMaxDup(second, first);

			first = second;
		}

		cout << result << endl;
	}
}

int getMaxDup(const string &first, const string &second)
{
	unsigned int begin = 0, match = 0;
	int n = first.length(), m = second.length();

	vector<int> pi = getPartialMatch(second);

	while (begin + match < n)
	{
		if (first[begin + match] == second[match])
		{
			match++;
			if (begin + match == n) return match;
		}
		else
		{
			if (match == 0) begin++;
			else 
			{
				begin += match - pi[match - 1];
				match = pi[match - 1];
			}
		}
	}
}

vector<int> getPartialMatch(const string &target)
{
	int size = target.size();
	int begin = 1, match = 0;
	vector<int> pi(size, 0);

	while (begin + match < size)
	{
		if (target[begin + match] == target[match])
		{
			match++;
			pi[begin + match - 1] = match;
		}
		else
		{
			if (match == 0) begin++;
			else
			{
				begin += match - pi[match - 1];
				match = pi[match - 1];
			}
		}
	}

	return pi;
}
