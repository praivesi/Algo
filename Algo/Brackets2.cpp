#include <iostream>
#include <stack>
#include <string>
#include <string.h>

using namespace std;

bool IsValid(const string str);
bool IsOpenSymbol(const char target);
bool IsSymmetric(const char source, const char target);

int main()
{
	int caseNum = 0;
	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		string brackets;

		std::getline(std::cin, brackets);

		// Process
		if (IsValid(brackets)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}

bool IsValid(const string str)
{
	stack<char> bstack;

	int arrLength = str.length() + 1;
	char* chars = new char[arrLength];
	strcpy_s(chars, arrLength, str.c_str());

	for (int i = 0; i < arrLength; i++)
	{
		if (bstack.size() == 0) bstack.push(chars[i]);
		else if (IsOpenSymbol(chars[i])) bstack.push(chars[i]);
		else if (IsSymmetric(bstack.top(), chars[i])) bstack.pop();
		else return false;
	}

	return true;
}

bool IsOpenSymbol(const char target)
{
	if (target == '(' || target == '{' || target == '[') return true;
	else return false;
}

bool IsSymmetric(const char source, const char target)
{
	if (source == '(' && target == ')') return true;
	else if (source == '{' && target == '}') return true;
	else if (source == '[' && target == ']') return true;
	else return false;
}
