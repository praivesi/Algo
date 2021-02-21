#include <iostream>
#include <vector>

using namespace std;

typedef int KeyType;

typedef struct Node
{
	KeyType key;
	int priority, size;
	Node *left, *right;

	Node(const KeyType& _key) : key(_key), priority(rand()),
		size(1), left(nullptr), right(nullptr) {}
	
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	void calcSize()
	{
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
} Node;

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key);
Node* insert(Node* root, Node* node);
Node* merge(Node* a, Node* b);
Node* erase(Node* root, KeyType key);
Node* kth(Node* root, int k);
int countLessThan(Node* root, KeyType key);
vector<int> solve(vector<int> &shifted, int n);

NodePair split(Node* root, KeyType key) {
	if (root == nullptr) return NodePair(nullptr, nullptr);

	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}

	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node) {
	if (root == nullptr) return node;

	if (root->priority < node->priority)
	{
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key) {
		root->setLeft(insert(root->left, node));
	}
	else root->setRight(insert(root->right, node));

	return root;
}

Node* merge(Node* a, Node* b)
{
	if (a == nullptr) return b;
	if (b == nullptr) return a;

	if (a->priority < b->priority)
	{
		b->setLeft(merge(a, b->left));
		return b;
	}

	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node* root, KeyType key)
{
	if (root == nullptr) return root;

	if (root->key == key)
	{
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	if (root->key > key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));

	return root;
}

Node* kth(Node* root, int k)
{
	int leftSize = 0;
	if (root->left != nullptr) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	else if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

int countLessThan(Node* root, KeyType key)
{
	if (root == nullptr) return 0;
	if (root->key >= key) return countLessThan(root->left, key);
	
	int ls = root->left ? root->left->size : 0;
	return ls + 1 + countLessThan(root->right, key);
}

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int n = 0, tmp = 0;
	vector<int> shifted, result;
	for (int i = 0; i < caseNum; i++)
	{
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			cin >> tmp;
			shifted.push_back(tmp);
		}

		result = solve(shifted, n);

		for (auto r : result) cout << r << " ";
		cout << endl;

		shifted.clear();
	}
}

vector<int> solve(vector<int> &shifted, int n)
{
	vector<int> original = vector<int>(n);

	Node* candidates = nullptr;
	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));

	int larger = -1;
	Node* kthNode = nullptr;
	for (int i = n - 1; i >= 0; i--)
	{
		larger = shifted[i];
		kthNode = kth(candidates, i + 1 - larger);
		original[i] = kthNode->key;
		candidates = erase(candidates, kthNode->key);

	}

	return original;
}
