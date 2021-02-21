#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int int_max = numeric_limits<int>::max();

typedef struct DifficultyNode
{
	int min, max;

	DifficultyNode() { min = int_max; max = 0; }
	DifficultyNode(int _min, int _max) : min(_min), max(_max) {}
} DifficultyNode;

typedef struct DifficultyQuery
{
	vector<DifficultyNode> querySource;
	int n;

	DifficultyQuery(vector<int> &array){
		n = array.size();
		querySource.resize(n * 4);
		init(array, 1, 0, n - 1);
	}

	DifficultyNode init(vector<int> &array, int node, int left, int right)
	{
		if (left == right)
		{
			querySource[node].min = array[left];
			querySource[node].max = array[left];

			return querySource[node];
		}

		int mid = (left + right) / 2;
		DifficultyNode leftNode = init(array, node * 2, left, mid);
		DifficultyNode rightNode = init(array, node * 2 + 1, mid + 1, right);

		querySource[node].min = min(leftNode.min, rightNode.min);
		querySource[node].max = max(leftNode.max, rightNode.max);

		return querySource[node];
	}

	DifficultyNode query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if (left == right) return querySource[node];

		if (right < nodeLeft || nodeRight < left) return DifficultyNode(int_max, 0);

		if (left <= nodeLeft && nodeRight <= right) return querySource[node];

		int nodeMid = (nodeLeft + nodeRight) / 2;

		DifficultyNode leftNode = query(left, right, node * 2, nodeLeft, nodeMid);
		DifficultyNode rightNode = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);


		return DifficultyNode(min(leftNode.min, rightNode.min), max(leftNode.max, rightNode.max));
	}

	int query(int left, int right)
	{
		if (left == right) return 0;

		DifficultyNode difficulty = query(left, right, 1, 0, n - 1);

		return difficulty.max - difficulty.min;
	}

} DifficultyQuery;

int main()
{
	int cn = 0;
	cin >> cn;

	int n = 0, q = 0;
	for (int ci = 0; ci < cn; ci++)
	{
		cin >> n >> q;

		vector<int> arr(n);

		for (int i = 0; i < n; i++) 
			cin >> arr[i];

		int left = 0, right = 0;
		for (int i = 0; i < q; i++)
		{
			cin >> left >> right;

			DifficultyQuery querySender(arr);

			int difficulty = querySender.query(left, right);
			cout << difficulty << endl;
		}

		arr.clear();
	}
}