#include <iostream>
#include <stdio.h>
#include "user.cpp"
using namespace std;

const int MAX = 105;

static char a[MAX_N][MAX_N];
static char b[MAX_N][MAX_N];
static int N, M;

int get_N(void) {
	return N;
}

char get_A(int row, int col) {
	if (0 <= row && row < N && 0 <= col && col < N) {
		return a[row][col];
	}
	return -1;
}

extern void init(int testcase);
extern int getSimilar(int M, char B[MAX_N][MAX_N]);

int main(void) {
	freopen("0Text.txt","r",stdin);
	//setbuf(stdout, NULL);
	int T; for (scanf("%d", &T); T--;) {
		int querySize;

		scanf("%d%d", &N, &querySize);

		for (int i = 0; i < N; i++) {
			scanf("%s", a[i]);
		}

		static int tc = 0;
		printf("#%d", ++tc);

		init(tc);

		for (int q = 0; q < querySize; q++) {
			scanf("%d", &M);
			for (int i = 0; i < M; i++) {
				scanf("%s", b[i]);
			}

			int queryanswer = getSimilar(M, b);
			printf(" %d", queryanswer);
		}
		printf("\n");
	}
	return 0;
}