#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>

#define MAX_BUFFER_SIZE 100010

using namespace std;

char p[MAX_BUFFER_SIZE];
string result;
int n;

typedef struct call
{
	int eCount;
	int sCount;
	int peCount;
	int psCount;
	char direction;

} call;


string traversal();

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input
		cin >> n;
		cin.ignore();
		cin.getline(p, MAX_BUFFER_SIZE);

		// Process
		result = traversal();

		// Output
		cout << "CASE #" << (cIter + 1) << ": " << result << endl;
	}
}

string traversal()
{
	stack<call> callStack;
	callStack.push(call{ 0, 0, 0, 0, 'N' });
	bool ret = true;
	char retDirection = 'N';

	while (callStack.size() != 2 * n - 1)
	{
		call prevCall = callStack.top();
		
		int eCount = prevCall.eCount, sCount = prevCall.sCount;
		int peCount = prevCall.peCount, psCount = prevCall.psCount;

		if (eCount == peCount && sCount == psCount)
		{
			if ((p[peCount + psCount] == 'E' && sCount == n - 1) ||
				(p[peCount + psCount] == 'S' && eCount == n - 1))
			{
				ret = false;
				retDirection = callStack.top().direction;

				callStack.pop();

				continue;
			}

			if (p[peCount + psCount] == 'E')
			{
				sCount++;
				peCount++;

				callStack.push(call{ eCount, sCount, peCount, psCount, 'S' });
			}
			else
			{
				eCount++;
				psCount++;

				callStack.push(call{ eCount, sCount, peCount, psCount, 'E' });
			}
		}
		else
		{
			if (ret == false)
			{
				if (retDirection == 'S')
				{
					retDirection = callStack.top().direction;
					callStack.pop();
				}
				else
				{
					if (sCount != n - 1)
					{
						ret = true;

						callStack.push(call{ eCount, sCount + 1, peCount, psCount, 'S' });
					}
					else
					{
						retDirection = callStack.top().direction;
						callStack.pop();
					}

				}
			}
			else
			{
				if (p[peCount + psCount] == 'E') peCount++;
				else psCount++;

				if (eCount != n - 1)
					callStack.push(call{ eCount + 1, sCount, peCount, psCount, 'E' });
				else
					callStack.push(call{ eCount, sCount + 1, peCount, psCount, 'S' });
			}
		}
	}

	string s = "";
	while (callStack.empty() == false)
	{
		s += callStack.top().direction;
		callStack.pop();
	}

	//s = s.substr(0, s.length() - 1);
	//reverse(s.begin(), s.end());

	string retS = "";
	for (int i = s.length() - 2; i >= 0; i--)
	{
		retS += s.at(i);
	}

	return retS;

	/*
	if (eCount == n || sCount == n) return false;
	if (eCount == n - 1 && sCount == n - 1) return true;

	if (eCount == peCount && sCount == psCount)
	{
		if (p[peCount + psCount] == 'E')
		{
			result[eCount + sCount] = 'S';
			return traversal(eCount, sCount + 1, peCount + 1, psCount);
		}
		else
		{
			result[eCount + sCount] = 'E';
			return traversal(eCount + 1, sCount, peCount, psCount + 1);
		}
	}
	else
	{
		int nextPECount = peCount, nextPSCount = psCount;
		if (p[peCount + psCount] == 'E') nextPECount++;
		else nextPSCount++;

		result[eCount + sCount] = 'E';
		if (traversal(eCount + 1, sCount, nextPECount, nextPSCount)) return true;

		result[eCount + sCount] = NULL;

		result[eCount + sCount] = 'S';
		if (traversal(eCount, sCount + 1, nextPECount, nextPSCount)) return true;
		else return false;
	}
	*/
}