#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

typedef struct timeSheet
{
	int startTime;
	int endTime;
} timeSheet;

vector<timeSheet*> schedule;

int main()
{
	int caseNum = 0;
	cin >> caseNum;
	cin.ignore();

	for (int cIter = 0; cIter < caseNum; cIter++)
	{
		int teamNum = 0;
		cin >> teamNum;

		for (int tIter = 0; tIter < teamNum; tIter++)
		{
			int a = 0, b = 0, c = 0, d = 0;
			cin >> a >> b >> c >> d;
			timeSheet* teamSchedule = new timeSheet[2];

			teamSchedule[0].startTime = a;
			teamSchedule[0].endTime = b;
			teamSchedule[1].startTime = c;
			teamSchedule[1].endTime = d;

			schedule.push_back(teamSchedule);
		}

		// Process
		for (auto & teamSchedule : schedule)
		{
			cout << "TEAM SCHEDULE: ";
			cout << teamSchedule[0].startTime << " " << teamSchedule[0].endTime << " "
				<< teamSchedule[1].startTime << " " << teamSchedule[1].endTime << endl;
		}

		// Clear
		schedule.clear();
	}

	_getch();
}