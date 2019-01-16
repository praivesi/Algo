#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int MAX_NUMBER_SIZE = 200000;

vector<int> multiply(const vector<int> &a, const vector<int> &b);
void normalize(vector<int> &c);
int getLength(char *arr);

int main()
{
	int caseNum = 0;
	char firstInput[MAX_NUMBER_SIZE], secondInput[MAX_NUMBER_SIZE];
	vector<int> first, second;

	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		cin.getline(firstInput, MAX_NUMBER_SIZE);
		cin.getline(secondInput, MAX_NUMBER_SIZE);

		first.clear();
		second.clear();

		for (int i = getLength(firstInput) - 1; i >= 0; i--)
		{
			first.push_back(firstInput[i] - '0');
		}
		for (int i = getLength(secondInput) - 1; i >= 0; i--)
		{
			second.push_back(secondInput[i] - '0');
		}

		clock_t begin, end;

		begin = clock();
		auto result = multiply(first, second);
		end = clock();

		cout << cIter + 1 << " th Time elapsed = " << (end - begin) << " ms" << endl;
		for (int i = result.size() - 1; i >= 0; i--)
		{
			cout << result[i];
		}
		cout << endl << endl;
	}
}

vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
	vector<int> c(a.size() + b.size() + 1);
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			c[i + j] += a[i] * b[j];
		}
	}

	normalize(c);

	return c;
}

void normalize(vector<int> &c)
{
	c.push_back(0);

	for (int i = 0; i < c.size() - 1; i++)
	{
		if (c[i] < 0)
		{
			int borrow = (abs(c[i]) + 9) / 10;
			c[i + 1] -= borrow;
			c[i] += borrow * 10;
		}
		else
		{
			c[i + 1] += c[i] / 10;
			c[i] %= 10;
		}
	}
	while (c.size() > 1 && c.back() == 0) c.pop_back();
}

int getLength(char *arr)
{
	int cnt = 0;
	while (arr[cnt] != NULL)
	{
		cnt++;
	}
	return cnt;
}