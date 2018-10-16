//https://www.acmicpc.net/problem/1600
//BOJ 1600 ¸»ÀÌ µÇ°íÇÂ ¿ø¼þÀÌ
#pragma once
#include<iostream>
#include<queue>

using namespace std;
int k, w, h;
int info[200][200];
bool order[31][200][200];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int dr2[8] = { -1,-2,-2,-1,1,2,2,1 };
int dc2[8] = { -2,-1,1,2,-2,-1,1,2 };

struct COD {
	int r, c, k;
	COD() :r(0), c(0), k(0) {}
	COD(int r, int c, int k) :r(r), c(c), k(k) {}
};
queue<COD> que;


bool isout(COD p) {
	return p.r < 0 || p.r >= h || p.c < 0 || p.c >= w;
}

int bfs() {
	COD now(0, 0, k);
	order[k][now.r][now.c] = 1;

	que.push(now);

	int ti = 0;
	while (que.size()) {
		int cnt = que.size();

		while (cnt--) {
			now = que.front(); que.pop();
			if (now.r == h - 1 && now.c == w - 1) {
				return ti;
			}

			COD next;
			for (int d = 0; d < 4; d++) {
				next = now;

				next.r += dr[d];
				next.c += dc[d];

				if (isout(next)) continue;
				if (info[next.r][next.c] == 1) continue;

				if (order[next.k][next.r][next.c] == 0 || ti + 1 == order[next.k][next.r][next.c]) {
					if (order[next.k][next.r][next.c] == 0) {
						order[next.k][next.r][next.c] = ti + 1;
						que.push(next);
					}
				}
			}

			if (now.k) {
				for (int d = 0; d < 8; d++) {
					next = now;
					next.r += dr2[d];
					next.c += dc2[d];
					next.k--;

					if (isout(next) || info[next.r][next.c] == 1) continue;

					if (order[next.k][next.r][next.c] == 0 || (order[next.k][next.r][next.c] - 1 == cnt)) {
						if (order[next.k][next.r][next.c] == 0) {
							order[next.k][next.r][next.c] = order[now.k][now.r][now.c] + 1;
							que.push(next);
						}
					}
				}
			}
		}
		ti++;
	}
	return -1;
}

int BOJ1600() {
	cin >> k;
	cin >> w >> h;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> info[i][j];
		}
	}

	cout << bfs();
	return 0;
}
