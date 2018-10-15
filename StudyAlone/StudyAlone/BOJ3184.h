//https://www.acmicpc.net/problem/3184
//BOJ 3184 ¾ç
#pragma once
#include<iostream>

using namespace std;

struct COD {
	int r, c;
	COD() :r(0), c(0) {};
	COD(int r, int c) :r(r), c(c) {}
};

struct RES {
	int v, o;
	RES() :v(0), o(0) {}
	RES(int v, int o) : v(v), o(o) {}

	RES& operator+(RES a) {
		v += a.v;
		o += a.o;
		return *this;
	}
	RES& operator+=(RES a) {
		v += a.v;
		o += a.o;
		return *this;
	}
};

COD que[250 * 250];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

char info[250][251];
int visit[250][250];
int R, C;

RES bfs(int r, int c) {
	COD now(r, c);
	visit[now.r][now.c] = true;

	int s, e;
	s = e = 0;

	que[e++] = now;

	int num[2] = {};

	while (s != e) {
		now = que[s++];
		if (info[now.r][now.c] == 'v') num[0]++;
		else if (info[now.r][now.c] == 'o') num[1]++;

		for (int d = 0; d < 4; d++) {
			COD next = now;
			next.r += dr[d];
			next.c += dc[d];
			
			if (next.r < 0 || next.c < 0 || next.r >= R || next.c >= C) continue;
			if (info[next.r][next.c] == '#') continue;
			if (visit[next.r][next.c]) continue;
			visit[next.r][next.c] = true;

			que[e++] = next;
		}
	}

	RES res;
	if (num[0] < num[1]) res.v = 0, res.o = num[1];
	else res.v = num[0], res.o = 0;

	return res;
}

int BOJ3184() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		cin >> info[i];
	}

	RES res ;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (visit[i][j]) continue;
			if (info[i][j] != '#') {
				res += bfs(i, j);
			}
		}
	}
	cout << res.o << ' ' << res.v;
	return 0;
}
