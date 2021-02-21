#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct NaiveDisjointSet {
	vector<int> parent;
	NaiveDisjointSet(int n) : parent(n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int u) const {
		if (u == parent[u]) return u;
		return find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;
		parent[u] = v;
	}
};

struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v)
	{
		u = find(u); v = find(v);
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};

struct BipartiteUnionFind {
	vector<int> parent, enemy, size, rank;

	BipartiteUnionFind(int n)
		: parent(n), enemy(n, -1), size(n, 1), rank(n, 0) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	int merge(int u, int v) {
		if (u == -1 || v == -1) return max(u, v);

		u = find(u); v = find(v);
		if (u == v) return u;

		if (rank[u] > rank[v]) swap(u, v);
		if (rank[u] == rank[v]) rank[v]++;

		parent[u] = v;
		size[v] += size[u];

		return v;
	}

	bool ask(int u, int v) {
		u = find(u); v = find(v);
		if (enemy[u] == v) return false;

		int a = merge(u, v), b = merge(enemy[u], enemy[v]);

		enemy[a] = b;
		if (b != -1) enemy[b] = a;

		return true;
	}

	bool dis(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false;

		int a = merge(u, enemy[v]), b = merge(enemy[u], v);
		enemy[a] = b; enemy[b] = a;

		return true;
	}

	void swap(int &u, int &v)
	{
		int tmp = u;
		u = v;
		v = tmp;
	}
};

int maxParty(int n, const BipartiteUnionFind& buf);

int main()
{
	int cn = 0;
	cin >> cn;
	
	string input = "";
	int n = 0, m = 0, a = 0, b = 0;

	for (int ci = 0; ci < cn; ci++)
	{
		cin >> n >> m;

		bool valid = true;
		BipartiteUnionFind buf = BipartiteUnionFind(n);
		for (int i = 0; i < m; i++) {
			cin >> input >> a >> b;
			if (input == "ACK") {
				if (buf.ask(a, b) == false) {
					cout << "CONTRADICTION AT " << i + 1 << endl;
					valid = false;
					break;
				}
			}
			else if (input == "DIS") {
				if (buf.dis(a, b) == false) {
					cout << "CONTRADICTION AT " << i + 1 << endl;
					valid = false;
					break;
				}
			}
		}

		if (valid) {
			int peopleCount = maxParty(n, buf);

			cout << "MAX PARTY SIZE IS " << peopleCount << endl;
		}
	}
}

int maxParty(int n, const BipartiteUnionFind& buf) {
	int ret = 0;

	for (int node = 0; node < n; node++) {
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];

			if (enemy > node) continue;

			int mySize = buf.size[node];
			int enemySize = enemy == -1 ? 0 : buf.size[enemy];

			ret += max(mySize, enemySize);
		}
	}

	return ret;
}
