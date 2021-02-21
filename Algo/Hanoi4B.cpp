#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define PILLAR_COUNT 4
#define DISK_NUM_INFINITE 999999

#define PILLAR_1_MASK 0xFFF0000000000000
#define PILLAR_2_MASK 0x000FFF0000000000
#define PILLAR_3_MASK 0x000000FFF0000000
#define PILLAR_4_MASK 0x000000000FFF0000

unsigned int diskCnt = 0;

struct State {
	unsigned long long disks;
	unsigned int minDiskIdx[PILLAR_COUNT];

	State() {
		disks = 0;

		for (int i = 0; i < PILLAR_COUNT; i++)
		{
			minDiskIdx[i] = DISK_NUM_INFINITE;
		}
	}

	// For std::map insertion
	bool operator<(const State & operand) const {
		return disks < operand.disks;
	}

	void operator=(const State &operand) {
		disks = operand.disks;

		for (int i = 0; i < PILLAR_COUNT; i++)
		{
			minDiskIdx[i] = operand.minDiskIdx[i];
		}
	}

	bool operator==(const State &operand) const
	{
		for (int i = 0; i < PILLAR_COUNT; i++)
		{
			if (minDiskIdx[i] != operand.minDiskIdx[i]) return false;
		}

		return (disks == operand.disks);
	}

	bool insertDisk(int pillarIdx, int diskIdx)
	{
		if (diskIdx > minDiskIdx[pillarIdx]) return false; // inserting bigger disk than smallest disk in pillar is not valid

		unsigned long long diskBit = 1;

		diskBit <<= (12 * pillarIdx);
		diskBit <<= diskIdx;

		if ((disks & diskBit) != 0) return false; // duplicate insertion

		disks |= diskBit;

		minDiskIdx[pillarIdx] = diskIdx;

		return true;
	}

	bool moveDisk(int diskIdx, int fromPillarIdx, int toPillarIdx)
	{
		if (diskIdx != minDiskIdx[fromPillarIdx]) return false;
		if (diskIdx > minDiskIdx[toPillarIdx]) return false;
		bool validate = false;

		// Validate fromPillar
		unsigned long long fromDiskBit = 1;

		fromDiskBit <<= (12 * fromPillarIdx);
		fromDiskBit <<= diskIdx;

		validate = ((disks & fromDiskBit) != 0);
		if (!validate) return false;

		// Validate toPilar
		unsigned long long toDiskBit = 1;

		toDiskBit <<= (12 * toPillarIdx);
		toDiskBit <<= diskIdx;

		validate = ((disks & toDiskBit) == 0);
		if (!validate) return false;

		// Apply Movement
		disks &= ~fromDiskBit;
		disks |= toDiskBit;

		minDiskIdx[fromPillarIdx] = DISK_NUM_INFINITE;
		unsigned long long fdb = 1;
		fdb <<= (12 * fromPillarIdx);

		for (int i = 0; i < diskCnt; i++)
		{
			if ((disks & (fdb << i)) != 0)
			{
				minDiskIdx[fromPillarIdx] = i < minDiskIdx[fromPillarIdx] ? i : minDiskIdx[fromPillarIdx];

				break;
			}
		}

		minDiskIdx[toPillarIdx] = diskIdx;

		return true;
	}
};

queue<State> q;
map<State, int> cost;

int bfs(State &finishState);

int sgn(int x)
{
	if (x == 0) return 0;
	return x < 0 ? -1 : 1;
}

int inc(int x)
{
	return x < 0 ? x - 1 : x + 1;
}

int main()
{
	int caseCnt = 0;

	cin >> caseCnt;

	for (int cIter = 0; cIter < caseCnt; cIter++)
	{
		while (!q.empty()) { q.pop(); }
		cost.clear();

		cin.ignore();

		cin >> diskCnt;

		State startState, finishState;

		for (int pillarIdx = 0; pillarIdx < PILLAR_COUNT; pillarIdx++)
		{
			int pillarDiskCnt = 0;
			cin >> pillarDiskCnt;

			for (int existDiskIdx = 0; existDiskIdx < pillarDiskCnt; existDiskIdx++)
			{
				int diskNum = 0;
				cin >> diskNum;

				startState.insertDisk(pillarIdx, diskNum - 1);
			}
		}

		for (int pillarIdx = 0; pillarIdx < PILLAR_COUNT; pillarIdx++)
		{
			int pillarDiskCnt = 0;
			cin >> pillarDiskCnt;

			for (int existPillarIdx = 0; existPillarIdx < pillarDiskCnt; existPillarIdx++)
			{
				int diskNum = 0;
				cin >> diskNum;

				finishState.insertDisk(pillarIdx, diskNum - 1);
			}
		}

		q.push(startState);
		q.push(finishState);
		cost.insert(std::pair<State, int>(startState, 1));
		cost.insert(std::pair<State, int>(finishState, -1));

		int shortestPath = bfs(finishState);

		cout << shortestPath << endl;
	}
}

int bfs(State &finishState)
{
	while (!q.empty())
	{
		State curState = q.front();
		q.pop();

		for (int fromPillarIdx = 0; fromPillarIdx < PILLAR_COUNT; fromPillarIdx++)
		{
			for (int toPillarIdx = 0; toPillarIdx < PILLAR_COUNT; toPillarIdx++)
			{
				if (toPillarIdx == fromPillarIdx) continue;

				for (int moveDiskIdx = 0; moveDiskIdx < diskCnt; moveDiskIdx++)
				{
					State nextState = curState;

					if (nextState.moveDisk(moveDiskIdx, fromPillarIdx, toPillarIdx))
					{
						map<State, int>::iterator it = cost.find(nextState);

						if (it == cost.end())
						{
							cost.insert(std::pair<State, int>(nextState, inc(cost[curState])));
							q.push(nextState);
						}
						else if (sgn(cost[curState]) != sgn(cost[nextState]))
						{
							return abs(cost[curState]) + abs(cost[nextState]) - 1;
						}
					}
				}
			}
		}
	}

	return -1;
}
