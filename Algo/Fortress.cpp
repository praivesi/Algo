#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Node
{
	int x, y, r;
	int idx;
	vector<Node*> childs;

	Node(int _x, int _y, int _r, int _idx) : x(_x), y(_y), r(_r), idx(_idx) {}
} Node;

void getLongestLeafPath(Node* const root);
int height(Node* const root);
bool compareNode(Node* a, Node* b);
void PrintPrefix(Node* const root);
void Insert(Node* const root, Node* const node);
bool IsInside(Node* const outer, Node* const inner);
int sqrt(int x);

int longest = 0;

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	int n = 0;

	int x, y, r;
	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Read input & Create Tree
		cin >> n;
		cin >> x >> y >> r;

		Node* root = new Node(x, y, r, 0);

		vector<Node*> nodes;
		for (int i = 0; i < n - 1; i++)
		{
			cin >> x >> y >> r;
			Node* newNode = new Node(x, y, r, i + 1);
			nodes.push_back(newNode);
		}
		sort(nodes.begin(), nodes.end(), compareNode);

		for (auto& node : nodes)
			Insert(root, node);

		getLongestLeafPath(root);

		cout << longest << endl;
	}
}

void getLongestLeafPath(Node* const root)
{
	longest = 0;

	int h = height(root);

	longest = max(longest, h);
}

int height(Node* const root)
{
	vector<int> heights;

	for (auto& child : root->childs)
		heights.push_back(height(child));

	if (heights.empty()) return 0;

	sort(heights.begin(), heights.end());

	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 1] + heights[heights.size() - 2]);

	return heights.back() + 1;
}

bool compareNode(Node* a, Node* b)
{
	return a->r > b->r;
}

void PrintPrefix(Node* const root)
{
	cout << root->idx << "(" << root->x << ", " << root->y << ", " << root->r << ")" << endl;

	for (auto& child : root->childs)
		PrintPrefix(child);
}

// node는 무조건 root에 포함된다고 가정
void Insert(Node* const root, Node* const node)
{
	if (root->childs.size() == 0)
	{
		root->childs.push_back(node);
		return;
	}

	for (auto& child : root->childs)
	{
		if (IsInside(child, node))
		{
			Insert(child, node);

			return;
		}
	}

	root->childs.push_back(node);
}

bool IsInside(Node* const outer, Node* const inner)
{
	if (outer->r < inner->r) return false;

	return sqrt(outer->x - inner->x) + sqrt(outer->y - inner->y) <= sqrt(outer->r);
}

int sqrt(int x)
{
	return x * x;
}
