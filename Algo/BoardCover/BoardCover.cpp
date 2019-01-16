#include <iostream>
#include <vector>

using namespace std;

const int MAX_WIDTH = 20;
const int coverType[4][3][2] = {
	{{0, 0}, {1, 0}, {1, -1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {0, 1}}
};

int boardHeight = 0, boardWidth = 0;

int cover(vector<vector<int>> &board);
bool set(vector<vector<int>> &board, int y, int x, int type, int flip);

int main()
{
	int caseNum = 0;
	string inputBuffer;
	char widthBuffer[MAX_WIDTH];

	vector<vector<int>> board;

	cin >> caseNum;

	for (int caseIter = 0; caseIter < caseNum; caseIter++)
	{
		cin >> boardHeight >> boardWidth;

		// clear cin
		cin.ignore();

		// clear buffer
		memset(widthBuffer, 0, MAX_WIDTH);

		// clear board
		board.clear();

		for (int hIter = 0; hIter < boardHeight; hIter++)
		{
			cin.getline(widthBuffer, MAX_WIDTH);

			// fill board data from input
			board.push_back(vector<int>(boardWidth));
			for (int wIter = 0; wIter < boardWidth; wIter++)
			{
				if (widthBuffer[wIter] == '#') { board[hIter][wIter] = 1; }
				else if(widthBuffer[wIter] == '.') { board[hIter][wIter] = 0; }
				else { cout << "Invalid Input" << endl; }
			}
		}

		cout << cover(board) << endl;
	}
}

int cover(vector<vector<int>> &board)
{
	int y = -1, x = -1;

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (board[i][j] == 0)
			{
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	
	if (y == -1) return 1;

	int ret = 0;
	for (int type = 0; type < 4; type++)
	{
		if (set(board, y, x, type, 1))
		{
			ret += cover(board);
		}
		set(board, y, x, type, -1);
	}

	return ret;
}

bool set(vector<vector<int>> &board, int y, int x, int type, int flip)
{
	bool ok = true;

	for (int i = 0; i < 3; i++)
	{
		int dy = y + coverType[type][i][0];
		int dx = x + coverType[type][i][1];
		if (dy < 0 || dy >= boardHeight || dx < 0 || dx >= boardWidth) ok = false;
		else if ((board[dy][dx] += flip) > 1) ok = false;
	}
	
	return ok;
}
