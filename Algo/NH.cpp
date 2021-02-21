#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <conio.h>

using namespace std;

const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'A'; }

typedef struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;

	TrieNode* fail;
	vector<int> output;

	TrieNode() : terminal(-1), fail(nullptr) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	void insert(const char* key, int id) {
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == nullptr) return nullptr;
		else return children[next]->find(key + 1);
	}
} TrieNode;

void computeFailFunc(TrieNode* root) {
	queue<TrieNode*> q;
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;

			if (here == root)
				child->fail = root;
			else
			{
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == nullptr)
					t = t->fail;
				
				// if(t->children[edge]) child->fail = t->children[edge];    <------ 요건 안됨?
				if (t->children[edge]) t = t->children[edge];
				child->fail = t;

				child->output = child->fail->output;
				if (child->terminal != -1)
					child->output.push_back(child->terminal);

				q.push(child);
			}
		}
	}
}

vector<pair<int, int>> ahoCorasick(const string& s, TrieNode* root) {
	vector<pair<int, int>> ret;
	TrieNode* state = root;

	for (int i = 0; i < s.size(); i++) {
		int chr = toNumber(s[i]);

		// 실패 연결 타고 올라감
		while (state != root && state->children[chr] == nullptr)
			state = state->fail;
		if (state->children[chr]) state = state->children[chr];  // <----------- 다시 시작하는 지점
		//////////////////////////////////////////////////////////////

		for (int j = 0; j < state->output.size(); j++)
			ret.push_back(make_pair(i, state->output[j]));
	}

	return ret;
}


