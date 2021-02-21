#include <iostream>
#include <vector>

using namespace std;

typedef struct node
{
	node* left;
	node* right;
	int key;

	node()
	{
		left = nullptr;
		right = nullptr;
		key = 0;
	}
} node;

vector<int> TraversalPostfix(const node* root);
node* GetTree(const vector<int> &prefix, const vector<int> &infix);

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int nodeCnt = 0;
	vector<int> prefix, infix;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		prefix.clear(); infix.clear();

		cin >> nodeCnt;

		int num = 0;
		for (int i = 0; i < nodeCnt; i++)
		{
			cin >> num;
			prefix.push_back(num);
		}

		for (int i = 0; i < nodeCnt; i++)
		{
			cin >> num;
			infix.push_back(num);
		}


		node* tree = GetTree(prefix, infix);
		vector<int> postfix = TraversalPostfix(tree);

		for (auto v : postfix)
		{
			cout << v << " ";
		}
		cout << endl;
	}
}

vector<int> TraversalPostfix(const node* root)
{
	if (root == nullptr) return vector<int>();

	vector<int> postfix;

	vector<int> leftPostfix = TraversalPostfix(root->left);
	postfix.insert(postfix.end(), leftPostfix.begin(), leftPostfix.end());

	vector<int> rightPostfix = TraversalPostfix(root->right);
	postfix.insert(postfix.end(), rightPostfix.begin(), rightPostfix.end());

	postfix.push_back(root->key);

	return postfix;
}

node* GetTree(const vector<int> &prefix, const vector<int> &infix)
{
	if (prefix.size() == 0 || infix.size() == 0) return nullptr;

	node* root = new node();
	root->key = prefix.front();

	int leftSize = 0, rightSize = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == root->key)
		{
			leftSize = i;
			rightSize = infix.size() - i - 1;

			break;
		}
	}

	auto leftPrefix = vector<int>(prefix.begin() + 1, prefix.begin() + leftSize + 1);
	auto leftInfix = vector<int>(infix.begin(), infix.begin() + leftSize);
	auto rightPrefix = vector<int>(prefix.begin() + leftSize + 1, prefix.end());
	auto rightInfix = vector<int>(infix.begin() + leftSize + 1, infix.end());

	root->left = GetTree(leftPrefix, leftInfix);
	root->right = GetTree(rightPrefix, rightInfix);

	return root;
}