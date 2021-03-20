#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <memory.h>
#include"user.cpp"

#define MAX_NUMBER	6
#define DUP_NUM		4
#define BOARD_ROW	5
#define BOARD_COL	5
#define MAX_MOVE	500

const int DIR[][2] = {
	-1, 0,	// UP
	1, 0,	// DOWN
	0, -1,	// LEFT
	0, 1	// RIGHT
};

extern void user(int board[BOARD_ROW][BOARD_COL], const int target[BOARD_ROW - 2][BOARD_COL - 2]);

static int board[BOARD_ROW][BOARD_COL];
static int target[BOARD_ROW - 2][BOARD_COL - 2];
static int nMove;
static int mSeed;

static int mrand(int num)
{
	mSeed = mSeed * 1103515245 + 37209;
	if (mSeed < 0) mSeed *= -1;
	return ((mSeed >> 8) % num);
}

static void makeBoard(int board[BOARD_ROW][BOARD_COL])
{
	int row = 0;
	int col = 0;
	int num = 1;
	int cnt = 0;

	memset(board, 0, BOARD_ROW * BOARD_COL * sizeof(int));

	for (int i = 0; i < BOARD_ROW * BOARD_COL - 1; ++i) {
		board[row][col] = num;

		if (++cnt >= DUP_NUM) {
			++num;
			cnt = 0;
		}

		if (++col >= BOARD_COL) {
			++row;
			col = 0;
		}
	}
}

static void makeRandomBoard(int board[BOARD_ROW][BOARD_COL])
{
	int num = 1;
	int cnt = 0;

	memset(board, -1, BOARD_ROW * BOARD_COL * sizeof(int));

	while (true) {
		int row = mrand(BOARD_ROW);
		int col = mrand(BOARD_COL);

		if (row > 0 && row < BOARD_ROW - 1 && col > 0 && col < BOARD_COL - 1)
			continue;

		board[row][col] = 0;
		break;
	}

	while (num <= MAX_NUMBER) {
		int row = mrand(BOARD_ROW);
		int col = mrand(BOARD_COL);

		if (board[row][col] != -1)
			continue;

		board[row][col] = num;

		if (++cnt >= DUP_NUM) {
			++num;
			cnt = 0;
		}
	}
}

static bool internalMove(int& row, int& col, int dir)
{
	int nrow = DIR[dir][0] + row;
	int ncol = DIR[dir][1] + col;

	if (nrow < 0 || nrow >= BOARD_ROW)
		return false;
	if (ncol < 0 || ncol >= BOARD_COL)
		return false;

	board[row][col] = board[nrow][ncol];

	row = nrow;
	col = ncol;
	board[row][col] = 0;
	return true;
}

static void shuffle(int board[BOARD_ROW][BOARD_COL], int cnt)
{
	int row, col;

	for (row = 0; row < BOARD_ROW; ++row) {
		for (col = 0; col < BOARD_COL; ++col) {
			if (!board[row][col])
				goto FOUND;
		}
	}
FOUND:

	while (cnt > 0) {
		int dir = mrand(4);
		int nrow = DIR[dir][0] + row;
		int ncol = DIR[dir][1] + col;

		if (!internalMove(row, col, dir))
			continue;
		--cnt;
	}
}

void Move(int dir)
{
	int row, col;

	for (row = 0; row < BOARD_ROW; ++row) {
		for (col = 0; col < BOARD_COL; ++col) {
			if (!board[row][col])
				goto FOUND;
		}
	}
	return;
FOUND:

	internalMove(row, col, dir);
	++nMove;
}

int main()
{
	int nTC = 10;
	int nShuffle = 10000;
	int userBoard[BOARD_ROW][BOARD_COL];
	int userTarget[BOARD_ROW - 2][BOARD_COL - 2];
	int totalScore = 0;

	//freopen("input.txt", "r", stdin);
	// scanf("%d", &nTC);

	for (int tc = 1; tc <= nTC; ++tc) {
		// scanf("%d", &mSeed);
        mSeed = mrand(2098);
		makeRandomBoard(board);

		for (int row = 0; row < BOARD_ROW - 2; ++row)
			memcpy(target[row], &board[row + 1][1], sizeof(int) * (BOARD_COL - 2));

		shuffle(board, nShuffle);

		memcpy(userBoard, board, BOARD_ROW * BOARD_COL * sizeof(int));
		memcpy(userTarget, target, (BOARD_ROW - 2) * (BOARD_COL - 2) * sizeof(int));

		nMove = 0;
		user(userBoard, userTarget);
		for (int row = 0; row < BOARD_ROW - 2; ++row) {
			if (memcmp(target[row], &board[row + 1][1], sizeof(int) * (BOARD_COL - 2))) {
				nMove = MAX_MOVE;
				break;
			}
		}

		if (nMove > MAX_MOVE)
			nMove = MAX_MOVE;

		int score = MAX_MOVE - nMove;
		printf("#%d %d\n", tc, score);
		totalScore += score;
	}
	printf("TotalScore = %d\n", totalScore);
	return 0;
}