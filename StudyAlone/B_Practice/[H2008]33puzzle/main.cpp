#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
int tc;

#include<stdio.h>
#include"user.cpp"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
int total = 0;


extern void solve(int board[5][5], int pattern[3][3], int callCntLimit);

static int orgBoard[5][5];
static int orgPattern[3][3];
static int emptyY, emptyX;
static int callCnt;

bool swap(int dir) {
	int dy[4] = { -1, 0, 1, 0 };
	int dx[4] = { 0, 1, 0, -1 };

	++callCnt;

	if (dir < UP || dir > LEFT) {
		return false;
	}

	int newY = emptyY + dy[dir];
	int newX = emptyX + dx[dir];

	if (newY < 0 || newY >= 5 || newX < 0 || newX >= 5) {
		return false;
	}

	orgBoard[emptyY][emptyX] = orgBoard[newY][newX];
	orgBoard[newY][newX] = 0;
	emptyY = newY;
	emptyX = newX;

	return true;
}

static bool run() {

	int board[5][5];
	int pattern[3][3];
	int callCntLimit;

	scanf("%d", &callCntLimit);

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			scanf("%d", &board[i][j]);

			orgBoard[i][j] = board[i][j];

			if (board[i][j] == 0) {
				emptyY = i;
				emptyX = j;
			}
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%d", &pattern[i][j]);

			orgPattern[i][j] = pattern[i][j];
		}
	}

	callCnt = 0;

	solve(board, pattern, callCntLimit);

	bool isCorrect = (callCnt <= callCntLimit);
	printf("%d\n", callCnt);
	total+= callCnt;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (orgBoard[i + 1][j + 1] != orgPattern[i][j]) {
				isCorrect = false;
			}
		}
	}

	return isCorrect;
}

int main(void) {

	setbuf(stdout, NULL);
	freopen("0Text.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (tc = 1; tc <= T; ++tc) {
		// printf("#%d ", tc); run();

		printf("#%d %d\n", tc, run() ? 100 : 0);
	}
	printf("%d\n", total);

	return 0;
}
