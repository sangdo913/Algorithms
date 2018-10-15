//https://www.acmicpc.net/problem/2933
//BOJ 2933 ¹Ì³×¶ö
#pragma once
#include<iostream>
#include<cstring>
#include<queue>

struct COD {
	int r, c;
	COD() :r(0), c(0) {}
	COD(int r, int c) :r(r), c(c) {}
};

using namespace std;
int R, C;
COD que[10000];
int f, r;
char arr[101][102];
bool visit[101][102];


int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };

bool isout(int r, int c) {
	return r < 1 || c < 0 || r > R || c >= C;
}

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int nfloor() {
	int len = 200;
	for (int i = 0; i < r; i++) {
		COD now = que[i];
		if (now.r == 1) return 0;
		int tlen = 0;
		int nr = now.r-1;
		int nc = now.c;

		while(nr  && visit[nr][nc] == 0 && arr[nr][nc] != 'x'){
			tlen++;
			nr -= 1;
		}
		if (visit[nr][nc] == 0) len = MIN(len, tlen);
	}
	return len;
}

void downlen(int len) {
	for (int i = 0; i < r; i++) {
		COD now = que[i];
		arr[now.r - len][now.c] = 'x';
	}
}

void vclear() {
	for (int i = 0; i < r; i++) {
		COD now = que[i];

		visit[now.r][now.c] = 0;
	}
}

void setarr(char c) {
	for (int i = 0; i < r; i++) {
		COD now = que[i];
		arr[now.r][now.c] = c;
	}
}

void bfs(int sr, int sc, int d) {
	while (!isout(sr, sc) && arr[sr][sc] != 'x') {
		sc += dc[d];
		sr += dr[d];
	}

	if (arr[sr][sc] == 'x') {
		arr[sr][sc] = '.';

		for (int cd = 0; cd < 4; cd++) {
			f = r = 0;
			COD now = COD(sr + dr[cd], sc + dc[cd]);

			if (isout(now.r, now.c) || arr[now.r][now.c] != 'x') continue;
			visit[now.r][now.c] = true;
			que[r++] = now;

			while (f != r) {
				now = que[f++];

				for (int nd = 0; nd < 4; nd++) {
					COD next = now;
					next.r += dr[nd];
					next.c += dc[nd];

					if (isout(next.r,next.c) || visit[next.r][next.c] || arr[next.r][next.c] == '.') continue;
					visit[next.r][next.c] = true;

					que[r++] = next;
				}
			}

			setarr('.');
			int len = nfloor();
			vclear();

			if (len) {
				downlen(len);
				return;
			}
			else setarr('x');
		}
	}
}

int BOJ2933() {
	cin >> R >> C;

	for (int i = R; i >= 1; i--) {
		cin >> arr[i];
	}

	int sc[2] = { 0,C-1 };
	int dir = 0;
	int n;
	cin >> n;

	while (n--) {
		int r;
		cin >> r;
		bfs(r, sc[dir & 1], dir & 1);
		dir++;
	}

	for (int i = R; i >= 1; i--) cout << arr[i] <<'\n';
	return 0;
}
