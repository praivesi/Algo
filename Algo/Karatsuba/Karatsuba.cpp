#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <time.h>
#include <limits.h>
#include <conio.h>

using namespace std;

const unsigned int MAX_NUMBER_SIZE = 200000;

vector<int> karatsuba(vector<int> &a, vector<int> &b);
void exponential(vector<int> &a, int k);
void addTo(vector<int> &a, vector<int> &b);
void subFrom(vector<int> &a, vector<int> &b);
vector<int> multiply(const vector<int> &a, const vector<int> &b);
void normalize(vector<int> &c);
int getLength(char *arr);

int main()
{
	int caseNum = 0;
	char *firstInput, *secondInput;

	firstInput = new char[MAX_NUMBER_SIZE];
	secondInput = new char[MAX_NUMBER_SIZE];

	//char firstInput[MAX_NUMBER_SIZE], secondInput[MAX_NUMBER_SIZE];
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
		auto result = karatsuba(first, second);
		end = clock();

		cout << cIter + 1 << " th Time elapsed = " << end - begin << " ms" << endl;
		for (int i = result.size() - 1; i >= 0; i--)
		{
			cout << result[i];
		}
		cout << endl << endl;
	}
}

vector<int> karatsuba(vector<int> &a, vector<int> &b)
{
	int half = a.size() / 2;

	if (a.size() <= 50) return multiply(a, b);

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + half);
	vector<int> b1(b.begin() + half, b.end());

	vector<int> z0 = karatsuba(a0, b0);
	vector<int> z1 = karatsuba(a1, b1);
	addTo(a0, a1);
	addTo(b0, b1);
	vector<int> z2 = karatsuba(a0, b0);
	subFrom(z2, z0);
	subFrom(z2, z1);

	exponential(z1, half + half);
	exponential(z2, half);
	addTo(z1, z2);
	addTo(z1, z0);

	normalize(z1);
	return z1;
}

void exponential(vector<int> &a, int k)
{
	for (int i = 0; i < k; i++)
		a.insert(a.begin(), 0);
}

void addTo(vector<int> &a, vector<int> &b)
{
	int i;
	for (i = 0; i < a.size(); i++)
	{
		if (i < b.size()) a[i] += b[i];
	}

	while (i < b.size())
	{
		a.push_back(b[i]);
		i++;
	}
}

void subFrom(vector<int> &a, vector<int> &b)
{
	int i = 0;
	for (i = 0; i < a.size(); i++)
	{
		if (i < b.size()) a[i] -= b[i];
	}

	while (i < b.size())
	{
		a.push_back(-b[i]);
		i++;
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
