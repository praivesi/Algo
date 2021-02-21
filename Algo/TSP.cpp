#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <time.h>
#include <conio.h>

using namespace std;

const int INF = 999999;
const int MAX_N = 100;

int n;
double **dists;

double bruteForce_solve(int curTown, int visited);
double simplePruning_solve();
void simplePruning_search(vector<int>& path, vector<bool> &visited, double curLength);
double simpleHeuristic_solve();
void simpleHeuristic_search(vector<int>& path, vector<bool> &visited, double curLength);
double simpleHeuristic_heuristic(vector<bool> &visited);
double nearestHeuristic_solve();
void nearestHeuristic_search(vector<int> &path, vector<bool> &visited, double curLength);
double pathPruning_solve();
void pathPruning_search(vector<int> &path, vector<bool> &visited, double curLength);
bool pathSwapPruning_canBeShorten_heuristic(vector<int> &path);
bool pathReversePruning_canBeShorten_heuristic(vector<int> &path);

double funcCnt;
double best;

// Simple Heuristic variable
double minEdge[MAX_N];

// Nearest Heuristic variable
vector<int> nearest[MAX_N];

int main()
{
	int caseNum = 0;
	cin >> caseNum;

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		// Input & Allocate & Initialize
		cin >> n;

		dists = new double*[n];
		for (int i = 0; i < n; i++)
		{
			dists[i] = new double[n];
			for (int j = 0; j < n; j++)
				cin >> dists[i][j];
		}

		funcCnt = 0;

		// Process
		// 항상 0 번 마을부터 시작한다고 가정
		clock_t begin, end;

		begin = clock();
		//double shortestDist = bruteForce_solve(0, 0);
		//double shortestDist = simplePruning_solve();
		//double shortestDist = simpleHeuristic_solve();
		//double shortestDist = nearestHeuristic_solve();
		double shortestDist = pathPruning_solve();
		end = clock();

		// Output
		cout << "shortestDist = " << shortestDist << " ( n : " << n << ", funcCnt : " << funcCnt << ", time elapsed : " << (end - begin) << " milliseconds )" << endl;

		// Dispose
		for (int i = 0; i < n; i++)
			delete[]  dists[i];
		delete[] dists;
	}

	_getch();
}

/* Brute Force */
double bruteForce_solve(int curTown, int visited)
{
	if (visited == (1 << n) - 1) return dists[curTown][0];

	double ret = INF;

	for (int i = 0; i < n; i++)
	{
		if ((visited & (1 << i)) != 0) continue;
		if (i != curTown) ret = min(ret, dists[curTown][i] + bruteForce_solve(i, visited | (1 << i)));
	}

	return ret;
}

/* ====================================================================================================================== */

/* Simple Pruning */
double simplePruning_solve()
{
	vector<bool> visited(n, false);
	vector<int> path(1, 0);

	best = INF;
	visited[0] = true;

	simplePruning_search(path, visited, 0);

	return best;
}

void simplePruning_search(vector<int>& path, vector<bool> &visited, double curLength)
{
	funcCnt++;

	// Pruning
	if (best <= curLength) return;

	int here = path.back();

	if (path.size() == n)
	{
		best = min(best, curLength + dists[here][0]);
		return;
	}

	for (int next = 0; next < n; next++)
	{
		if (visited[next]) continue;
		
		path.push_back(next);
		visited[next] = true;
		
		simplePruning_search(path, visited, curLength + dists[here][next]);

		visited[next] = false;
		path.pop_back();
	}
}

/* ====================================================================================================================== */

/* Simple Heuristic (Get heuristic value from greedy algorithm)*/
double simpleHeuristic_solve()
{
	vector<bool> visited(n, false);
	vector<int> path(1, 0);

	best = INF;
	visited[0] = true;

	// initializing minEdge
	for (int i = 0; i < n; i++)
	{
		minEdge[i] = INF;
		for (int j = 0; j < n; j++)
			if (i != j) minEdge[i] = min(minEdge[i], dists[i][j]);
	}

	simpleHeuristic_search(path, visited, 0);

	return best;
}

void simpleHeuristic_search(vector<int>& path, vector<bool> &visited, double curLength)
{
	funcCnt++;

	// Simple Heuristic
	if (best <= curLength + simpleHeuristic_heuristic(visited)) return;

	int here = path.back();

	if (path.size() == n)
	{
		best = min(best, curLength + dists[here][0]);
		return;
	}

	for (int next = 0; next < n; next++)
	{
		if (visited[next]) continue;

		path.push_back(next);
		visited[next] = true;

		simpleHeuristic_search(path, visited, curLength + dists[here][next]);

		visited[next] = false;
		path.pop_back();
	}
}

double simpleHeuristic_heuristic(vector<bool> &visited)
{
	double ret = minEdge[0];
	for (int i = 0; i < n; i++)
		if (visited[i] == false)
			ret += minEdge[i];

	return ret;
}

/* ====================================================================================================================== */

/* Nearest Heuristic */
double nearestHeuristic_solve()
{
	best = INF;
	vector<int> path;
	vector<bool> visited(n, false);
	
	// initializing nearest
	for (int i = 0; i < n; i++)
	{
		vector<pair<double, int>> order;
		for (int j = 0; j < n; j++)
			if(i != j) order.push_back(make_pair(dists[i][j], j));
		sort(order.begin(), order.end());
		
		nearest[i].clear();
		for (auto o : order)
			nearest[i].push_back(o.second);
	}

	// Process
	path.push_back(0);
	visited[0] = true;

	nearestHeuristic_search(path, visited, 0);

	return best;
}

void nearestHeuristic_search(vector<int> &path, vector<bool> &visited, double curLength)
{
	funcCnt++;

	if (best <= curLength) return;

	int here = path.back();

	if (path.size() == n)
	{
		best = min(best, curLength + dists[here][0]);
		return;
	}

	for (auto next : nearest[here])
	{
		if (visited[next]) continue;

		path.push_back(next);
		visited[next] = true;

		nearestHeuristic_search(path, visited, curLength + dists[here][next]);

		visited[next] = false;
		path.pop_back();
	}
}

/* ====================================================================================================================== */

/* Path Swap Pruning */
double pathPruning_solve()
{
	best = INF;
	vector<int> path;
	vector<bool> visited(n, false);
	
	// Process
	path.push_back(0);
	visited[0] = true;

	pathPruning_search(path, visited, 0);

	return best;
}

void pathPruning_search(vector<int> &path, vector<bool> &visited, double curLength)
{
	funcCnt++;

	//if (pathSwapPruning_canBeShorten_heuristic(path)) return;
	if (pathReversePruning_canBeShorten_heuristic(path)) return;

	int here = path.back();

	if (path.size() == n)
	{
		best = min(best, curLength + dists[here][0]);
		/*
		double nextB = curLength + dists[here][0];
		if (best > nextB)
		{
			cout << "best changing .. from " << best << " to " << nextB << " ( " << funcCnt << " )" << endl;
			best = nextB;

			cout << "path : ";
			for (auto p : path)
				cout << p << " ";
			cout << endl;
		}
		*/

		return;
	}

	for(int next = 0; next < n; next++)
	{
		if (visited[next]) continue;

		path.push_back(next);
		visited[next] = true;

		pathPruning_search(path, visited, curLength + dists[here][next]);

		visited[next] = false;
		path.pop_back();
	}
}

bool pathSwapPruning_canBeShorten_heuristic(vector<int> &path)
{
	if (path.size() < 4) return false;

	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	
	return dists[p][a] + dists[b][q] > dists[p][b] + dists[a][q];
}

bool pathReversePruning_canBeShorten_heuristic(vector<int> &path)
{
	if (path.size() < 4) return false;

	int b = path[path.size() - 2];
	int q = path[path.size() - 1];

	int a, p;
	for (int i = 0; i < path.size() - 3; i++)
	{
		p = path[i];
		a = path[i + 1];

		if (dists[p][a] + dists[b][q] > dists[p][b] + dists[a][q]) return true;
	}

	return false;
}

/* ====================================================================================================================== */

/* Dynamic Programming */


/* ====================================================================================================================== */

/* Memoization */


/* ====================================================================================================================== */

/* MST (Minimum Spanning Tree) - Kruskal */
