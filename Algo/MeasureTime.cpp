#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}

		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};


long long countMoves(vector<int> &arr);

int main()
{
	int cn = 0;
	cin >> cn;

	int n = 0;
	for (int ci = 0; ci < cn; ci++)
	{
		cin >> n;
		vector<int> arr = vector<int>(n);
		for (int i = 0; i < n; i++)
			cin >> arr[i];

		cout << countMoves(arr) << endl;
	}
}

long long countMoves(vector<int> &arr)
{
	FenwickTree tree = FenwickTree(1000000);
	long long ret = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		ret += tree.sum(999999) - tree.sum(arr[i]);
		tree.add(arr[i], 1);
	}

	return ret;
}