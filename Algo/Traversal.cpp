#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;

int n;
vector<int> preorder;
vector<int> inorder;

void printPostOrder(const vector<int> &preorder, const vector<int> &inorder);
vector<int> slice(const vector<int> &v, int start, int end);

int main()
{
	int caseNum = 0;

	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Initialize
		preorder.clear();
		inorder.clear();

		// Input
		cin >> n;

		int item;

		for (int i = 0; i < n; i++)
		{
			cin >> item;
			preorder.push_back(item);
		}

		for (int i = 0; i < n; i++)
		{
			cin >> item;
			inorder.push_back(item);
		}

		// Process
		printPostOrder(preorder, inorder);
	}

	_getch();
}

void printPostOrder(const vector<int> &preorder, const vector<int> &inorder)
{

	if (preorder.empty()) return;

	int currentN = preorder.size();

	if (currentN == 1)
	{
		cout << preorder[0] << " ";
		return;
	}

	int rootItem = preorder[0];
	int L = find(inorder.begin(), inorder.end(), rootItem) - inorder.begin();

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, currentN), slice(inorder, L + 1, currentN));
	cout << rootItem << ' ';
}

vector<int> slice(const vector<int> &v, int start, int end)
{
	return vector<int>(v.begin() + start, v.begin() + end);
}
