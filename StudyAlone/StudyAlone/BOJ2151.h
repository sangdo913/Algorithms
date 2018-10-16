//https://www.acmicpc.net/problem/2151
//BOJ2151 거울 설치
#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;


struct COD {
	int r, c, d, cnt;
	COD() :r(0), c(0), d(0), cnt(0) {}
	COD(int p[2]) :r(p[0]), c(p[1]), d(-1), cnt(-1) {}
	COD(int r, int c) :r(r), c(c), d(0), cnt(0) {}
	COD(int r, int c, int d, int cnt) : r(r), c(c), d(d), cnt(cnt) {}
};

int n;
char info[50][51];
int visit[50][50][4];

bool isout(COD p) {
	return p.r < 0 || p.c < 0 || p.r >= n || p.c >= n;
}

struct cmp {
	bool operator()( COD c1, COD c2) {
		return c1.cnt > c2.cnt;
	}
};

priority_queue<COD,vector<COD>, cmp> que;

int p[2][2];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int bfs() {
	COD now(p[0]);
	for (int i = 0; i < 4; i++) {
		que.push(COD(p[0][0], p[0][1], i, 0));
		visit[p[0][0]][p[0][1]][i] = 0;
	}


	while (que.size()) {
		now = que.top(); que.pop();
		if (now.r == p[1][0] &&now.c == p[1][1] ) return now.cnt;

		for (int d = -1; d <= 1; d++) {
			int nd = (4 + d + now.d) % 4;
			if (info[now.r][now.c] != '!' && now.d != nd) continue;

			COD next = now;
			next.cnt += nd != next.d;
			next.r += dr[nd];
			next.c += dc[nd];
			next.d = nd;

			if (isout(next) || info[next.r][next.c] == '*') continue;
			if (visit[next.r][next.c][nd] <= next.cnt) continue;
			visit[next.r][next.c][nd] = next.cnt;

			que.push(next);
		}
	}
	return -1;
}

int BOJ2151() {
	cin >> n;
	int cnt = 0;

	memset(visit, 0x3f, sizeof(visit));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> info[i][j];
			if (info[i][j] == '#') p[cnt][0] = i, p[cnt++][1] = j;
		}
	}

	cout << bfs();
	return 0;
}