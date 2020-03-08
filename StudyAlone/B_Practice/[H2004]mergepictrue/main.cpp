#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <memory.h>
#include"user.cpp"

#define MAX_PICTURE_SIZE 1000
#define MAX_PIECE_SIZE 100
#define MAXN 1500

extern void mergePictures(int N, int M, int K, char pictures[MAXN][MAX_PIECE_SIZE][MAX_PIECE_SIZE]);

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static char mergedPicture[MAX_PICTURE_SIZE][MAX_PICTURE_SIZE];
static char ret[MAX_PICTURE_SIZE][MAX_PICTURE_SIZE];
static char scrap[MAXN][MAX_PIECE_SIZE][MAX_PIECE_SIZE];
static int scrapIdx[MAX_PICTURE_SIZE][MAX_PICTURE_SIZE];

static int seed, N, M, K;
static int flag;
static int PASS;
static int FAIL = 0;
static bool used[MAXN];

static int dx[4] = { 1, 0, -1, 0 };
static int dy[4] = { 0, 1, 0, -1 };

bool setPicture(int id, int x, int y) {
	if (id < 1 || id > N - 1)
		return false;

	if (x < 0 || y < 0 || x > K - M || y > K - M)
		return false;

	if (used[id] == true)
		return false;

	bool isMatch = false;
	for (int k = 0; k < 4 && !isMatch; k++) {
		for (int i = 1; i <= M - 2; i++) {
			int nx = x + dx[k] * i;
			int ny = y + dy[k] * i;

			if (nx < 0 || ny < 0 || nx > K - M || ny > K - M)
				break;

			if (scrapIdx[ny][nx] != -1) {
				isMatch = true;
				break;
			}
		}
	}

	if (!isMatch)
		return false;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (ret[y + i][x + j] != 0 && ret[y + i][x + j] != scrap[id][i][j])
				return false;
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			ret[y + i][x + j] = scrap[id][i][j];
		}
	}

	scrapIdx[y][x] = id;
	used[id] = true;
	return true;
}

static void makePicture(int size, int seed) {
	mSeed = seed;
	memset(mergedPicture, 0, sizeof(mergedPicture));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mergedPicture[i][j] = pseudo_rand() % 15 + 1;
}

static int run() {
	scanf("%d %d %d %d", &flag, &N, &K, &M);
	if (flag == 1) {
		for (int i = 0; i < K; i++)
			for (int j = 0; j < K; j++)
				scanf("%hhd", &mergedPicture[i][j]);
	}
	else {
		scanf("%d", &seed);
		makePicture(K, seed);
	}

	for (int i = 0; i < MAXN; i++)
		used[i] = false;

	for (int i = 0; i < MAX_PICTURE_SIZE; i++) {
		for (int j = 0; j < MAX_PICTURE_SIZE; j++) {
			ret[i][j] = 0;
			scrapIdx[i][j] = -1;
		}
	}

	int y, x;
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &y, &x);
		for (int j = 0; j < M; j++)
			for (int k = 0; k < M; k++)
				scrap[i][j][k] = mergedPicture[y + j][x + k];
	}

	scrapIdx[0][0] = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			ret[i][j] = mergedPicture[i][j];
		}
	}

	mergePictures(N, M, K, scrap);

	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			if (ret[i][j] != mergedPicture[i][j])
				return FAIL;

	return PASS;
}

int main() {
	setbuf(stdout, NULL);
	freopen("0Text.txt", "r", stdin);

	int T, tc;
	scanf("%d %d", &T, &PASS);
	for (tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run());
	}
	return 0;
}