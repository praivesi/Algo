#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef int KeyType;

// 이 함수들은 문제 풀 때 쓰이진 않지만 (C++ STL 의 priority_queue를 대신 사용) 
// 기왕 구현했으니 넣어둠
void push_heap(vector<KeyType> &heap, KeyType key);
void pop_heap(vector<KeyType> &heap);
void swap(int *a, int *b);

typedef struct Rng
{
	int seed, a, b;
	Rng(int _a, int _b) : a(_a), b(_b)
	{
		seed = 1983;
	}

	int next()
	{
		int prevSeed = seed;
		seed = (seed * (long long)a + b) % 20090711;

		return prevSeed;
	}
};

int main()
{
	int cn = 0;
	cin >> cn;

	for (int ci = 0; ci < cn; ci++)
	{
		int n, a, b;
		cin >> n >> a >> b;

		Rng rng = Rng(a, b);

		priority_queue<int, vector<int>, less<int>> maxHeap;
		priority_queue<int, vector<int>, greater<int>> minHeap;

		int medsum = 0;
		for (int i = 0; i < n; i++)
		{
			if(maxHeap.size() == minHeap.size()) maxHeap.push(rng.next());
			else minHeap.push(rng.next());

			if (maxHeap.empty() == false && minHeap.empty() == false &&
				maxHeap.top() > minHeap.top())
			{
				int a = maxHeap.top(), b = minHeap.top();
				maxHeap.pop(); minHeap.pop();
				maxHeap.push(b); minHeap.push(a);
			}

			medsum = (medsum + maxHeap.top()) % 20090711;
		}

		cout << medsum << endl;
	}
}

void push_heap(vector<KeyType> &heap, KeyType key)
{
	int idx = heap.size() - 1;

	while (idx > 0 && heap[idx] > heap[(idx - 1) / 2])
	{
		swap(&heap[idx], &heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}

void pop_heap(vector<KeyType> &heap)
{
	heap[0] = heap.back();
	heap.pop_back();

	int here = 0;
	while (true)
	{
		int left = here * 2 + 1, right = here * 2 + 2;
		if (left >= heap.size()) break;

		int next = here;
		if (heap[next] < heap[left]) next = left;
		if (right < heap.size() && heap[next] < heap[right]) next = right;
		if (next == here) break;

		swap(&heap[here], &heap[next]);
		here = next;
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}