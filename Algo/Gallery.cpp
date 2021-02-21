#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//int counter = 0; <-- used in findCutertex() 
bool **gAdj;

int galleryNum = 0, hallwayNum = 0;

vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int installCount = 0;

// findCutVertex() 함수로는 gallery 그래프의 컴포넌트가 둘 이상일 경우를 캐치할 수 없음
//int findCutVertex(int here, bool isRoot, vector<int> & discovered, vector<bool> & isCutVertex);
int dfsForInstall(int here);
int installCamera();

int main()
{
	int caseNum = 0;
	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
#pragma region READ INPUT

		cin >> galleryNum >> hallwayNum;

		// Allocate adjacent
		gAdj = new bool*[galleryNum];
		for (int i = 0; i < galleryNum; i++)
			gAdj[i] = new bool[galleryNum] {false, };

		int hFrom = -1, hTo = -1;
		for (int hIter = 0; hIter < hallwayNum; hIter++)
		{
			cin >> hFrom >> hTo;
			gAdj[hFrom][hTo] = true;
		}
#pragma endregion

		int installCnt = installCamera();

	/*	vector<int> discovered(galleryNum);
		vector<bool> isCutVertex(galleryNum);
		for (int i = 0; i < discovered.size(); i++)
		{
			discovered[i] = -1;
			isCutVertex[i] = false;
		}

		for (int i = 0; i < galleryNum; i++)
		{
			if (discovered[i] != -1) continue;

			findCutVertex(i, true, discovered, isCutVertex);
		}*/

#pragma region OUTPUT
		cout << installCnt << endl;

	/*	cout << "CUT VERTEX: ";
		for (int i = 0; i < isCutVertex.size(); i++)
		{
			if (isCutVertex[i])
				cout << i << " ";
		}
		cout << endl;*/
#pragma endregion

#pragma region DISPOSE
		//counter = 0;
		for (int i = 0; i < galleryNum; i++)
			delete[] gAdj[i];
		delete[] gAdj;
#pragma endregion
	}
}

int dfsForInstall(int here)
{
	visited[here] = true;

	int children[3] = { 0, 0, 0 };

	for (int there = 0; there < galleryNum; there++)
	{
		if (gAdj[here][there] == false) continue;
		if (visited[there]) continue;

		++children[dfsForInstall(there)];
	}

	if (children[UNWATCHED])
	{
		installCount++;
		return INSTALLED;
	}

	if (children[INSTALLED])
		return WATCHED;

	return UNWATCHED;
}

int installCamera()
{
	installCount = 0;
	visited = vector<bool>(galleryNum, false);

	for (int u = 0; u < galleryNum; u++)
	{
		if (visited[u] == false && dfsForInstall(u) == UNWATCHED)
		{
			++installCount;
		}
	}

	return installCount;
}

//int findCutVertex(int here, bool isRoot, vector<int> & discovered, vector<bool> & isCutVertex)
//{
//	discovered[here] = counter++;
//
//	int childrenNum = 0;
//	int ret = discovered[here];
//
//	for (int there = 0; there < galleryNum; there++)
//	{
//		if (gAdj[here][there] == false) continue;
//
//		childrenNum++;
//
//		if (discovered[there] == -1)
//		{
//			int subtree = findCutVertex(there, false, discovered, isCutVertex);
//
//			if (isRoot == false && subtree >= discovered[here])
//				isCutVertex[here] = true;
//
//			ret = min(ret, subtree);
//		}
//		else
//		{
//			ret = min(ret, discovered[there]);
//		}
//	}
//
//	if (isRoot)
//		isCutVertex[here] = (childrenNum >= 2);
//
//	return ret;
//}