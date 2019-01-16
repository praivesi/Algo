#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int MAX_BUFFER_SIZE = 1024;

string flip(const char *input, int idx);

int main()
{
	int caseNum = 0;
	char inputBuffer[MAX_BUFFER_SIZE];

	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin.getline(inputBuffer, MAX_BUFFER_SIZE);

		string result = flip(inputBuffer, 0);

		cout << result << endl;
	}
}

string flip(const char *input, int idx)
{
	if (input[idx] == 'b') return "b";
	else if (input[idx] == 'w') return "w";
	else
	{
		string s[4] = { "", };

		idx++;
		for (int i = 0; i < 4; i++)
		{
			s[i] = flip(input, idx);
			idx += s[i].length();
		}

		return "x" + s[2] + s[3] + s[0] + s[1];
	}
}
