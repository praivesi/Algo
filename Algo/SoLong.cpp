#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'A'; }

typedef struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;
	int first;

	TrieNode() : terminal(-1), first(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	void insert(const char* key, int id) {
		if (first == -1)
			first = id;

		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			if (children[next] == nullptr)
				children[next] = new TrieNode();
			children[next]->insert(key + 1, id);
		}
	}

	int type(const char* key, int id)
	{
		if (*key == 0) return 0;
		if (first == id) return 1;

		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == nullptr) return nullptr;
		else return children[next]->find(key + 1);
	}
} TrieNode;

bool comparer(pair<int, string> a, pair<int, string> b)
{
	return a.first != b.first ? a.first > b.first : a.second < b.second;
}

int countKeys(TrieNode* trie, const char* word) {
	TrieNode* node = trie->find(word);
	if (node == nullptr || node->terminal == -1) return strlen(word);

	return trie->type(word, node->terminal);
}

int main()
{
	int cn = 0;
	cin >> cn;
	
	int n = 0, m = 0;
	vector<pair<int, string>> words;
	vector<string> inputs;
	for (int ci = 0; ci < cn; ci++)
	{
		cin >> n >> m;

		int priority = 0;
		string word = "";
		for (int i = 0; i < n; i++)
		{
			cin >> word >> priority;
			words.push_back(make_pair(priority, word));
		}

		std::sort(words.begin(), words.end(), comparer);

		for (int i = 0; i < n; i++)
			cout << "WORD : " << words[i].second << " / PRIORITY : " << words[i].first << endl;

		TrieNode* trie = new TrieNode();
		for (int i = 0; i < words.size(); i++)
			trie->insert(words[i].second.c_str(), i);
		trie->first = -1;

		string tmp = "";
		for (int i = 0; i < m; i++)
		{
			cin >> tmp;
			inputs.push_back(tmp);
		}

		for (int i = 0; i < m; i++)
			cout << "INPUT #" << i + 1 << inputs[i] << endl;

		int count = 0;
		for (int i = 0; i < m; i++)
			count += countKeys(trie, inputs[i].c_str());

		count += inputs.size() - 1;

		cout << "COUNT : " << count << endl;

		words.clear();
		inputs.clear();

		cout << "[ CASE END ]" << endl;
	}

	_getch();
}
