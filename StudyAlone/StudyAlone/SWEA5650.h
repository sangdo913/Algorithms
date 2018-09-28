//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo&categoryId=AWXRF8s6ezEDFAUo&categoryType=CODE
//SWEA 5650
//«…∫º ∞‘¿”
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

enum dir { UP = 0b0001, DOWN = 0b0010, LEFT = 0b0100, RIGHT = 0b1000};
int map[200][200];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int bcond[6] = { 0, LEFT|DOWN, LEFT | UP, RIGHT|UP, RIGHT|DOWN, 0};
int holes[20][2][2];
int hsize[20];
int n;
int bitD[4] = { 1,2,4,8 };
int bconv[6][8];

bool visit[200][200][4];

int go(int r, int c, int sr, int sc, int cnt, int d) {
	while (true) {
		if (cnt >= 0 && r == sr && c == sc) {
			return cnt;
		}

		if (map[r][c] == -1) return cnt;

		if (cnt == -1) cnt = 0;

		int next[2] = { r + dr[d], c + dc[d] };

		while (map[next[0]][next[1]] == 0) {
			if (next[0] == sr && next[1] == sc) return cnt;
			if (map[next[0]][next[1]] == -1) return cnt;
			next[0] += dr[d];
			next[1] += dc[d];
		}

		if (map[next[0]][next[1]] == -1) {
			return cnt;
		}

		if (map[next[0]][next[1]] < 6) {
			cnt++;
			if (bitD[d] & bcond[map[next[0]][next[1]]]) {
				d = bconv[map[next[0]][next[1]]][bitD[d]];
			}
			else {
				d ^= 1;
			}
		}
		else {
			int block = map[next[0]][next[1]];

			if (holes[block][0][0] == next[0] && holes[block][0][1] == next[1]) {
				next[0] = holes[block][1][0];
				next[1] = holes[block][1][1];
			}
			else {
				next[0] = holes[block][0][0];
				next[1] = holes[block][0][1];
			}
		}
		r = next[0], c = next[1];
	}
	return cnt;
}
int SWEA5650() {
	int t;
	cin >> t;

	bconv[1][LEFT] = 0;
	bconv[1][DOWN] = 3;
	bconv[2][LEFT] = 1;
	bconv[2][UP] = 3;
	bconv[3][RIGHT] = 1;
	bconv[3][UP] = 2;
	bconv[4][RIGHT] = 0;
	bconv[4][DOWN] = 2;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;
		f = r = 0;

		memset(visit, false, sizeof(visit));
		memset(hsize, 0, sizeof(hsize));

		for (int j = 0; j <= n + 1; j++) {
			map[0][j] = map[n + 1][j] = 5;
		}

		for (int i = 0; i <= n + 1; i++) {
			map[i][0] = map[i][n + 1] = 5;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
				if (map[i][j] >= 6 && map[i][j] <= 10) {
					holes[map[i][j]][hsize[map[i][j]]][0] = i;
					holes[map[i][j]][hsize[map[i][j]]++][1] = j;
				}
			}
		}

		int res = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == 0) {
					for (int d = 0; d < 4; d++) {
						if (visit[i][j][d]) continue;
						
						int r = i; int c = j;
						while (map[r][c] == 0) {
							r += dr[d]; c += dc[d];
							visit[i][j][d] = true;
						}

						r -= dr[d]; c -= dc[d];
						res = MAX(res, go(r, c, r, c, -1, d));
					}

				}

			}
		}
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}
