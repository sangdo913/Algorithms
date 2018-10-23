//https://www.acmicpc.net/problem/16234
//BOJ 16234 인구이동
#pragma once

#include<iostream>
#include<cstring>
using namespace std;

int info[2][51][51], le, ri,n, turn;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
bool check[51][51] = {};
int st[1000], top;
int rev[4] = { 1,0,3,2 };

struct COD { 
	int r, c;
	COD() :r(0), c(0) {} 
	COD(int r, int c) :r(r), c(c) {}
};

bool isout(int r, int c) { return r < 1 || c < 1 || r > n || c > n; }
int ABS(int i) { return i > 0 ? i : -i; }

bool bfs(int r, int c) {
	COD que[3000];
	COD st[3000];
	COD now(r, c);
	bool visit[4][51][51] = {};
	int s, e, top;
	top = s = e = 0;
	que[e++] = now;
	int num = 0;
	int size;
	bool instack[51][51] = {};

	while (s != e) {
		now = que[s++];
		if(!instack[now.r][now.c]) st[top++] = now, num += info[turn%2][now.r][now.c];
		instack[now.r][now.c] = true;

		for (int d = 0; d < 4; d++) {
			COD next = now;
			next.r += dr[d], next.c += dc[d];

			if (isout(next.r, next.c)) continue;
			if (ABS(info[turn%2][next.r][next.c] - info[turn%2][now.r][now.c]) < le || ABS(info[turn%2][next.r][next.c] - info[turn%2][now.r][now.c]) > ri) continue;
			if (check[next.r][next.c]) continue;
			if (visit[d][now.r][now.c]) continue;
			visit[d][now.r][now.c] = true;
			visit[rev[d]][next.r][next.c] = true;
			que[e++] = next;
		}
	}

	num /= top;
	bool res = false;

	while (top) {
		now = st[--top];
		check[now.r][now.c] = true;
		res |= info[turn%2][now.r][now.c] - num;
		info[(turn+1)%2][now.r][now.c] = num;
	}
	return res;
}
bool canmove() {
	memset(check, false, sizeof(check));

	bool res = false;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check[i][j]) continue;
			res |= bfs(i, j);
		}
	}
	return res;
}
int BOJ16234() {
	cin >> n >> le >> ri;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) cin >> info[0][i][j];
	}

	int res = 0;
	while (canmove()) turn++, res++;
	cout << res;
	return 0;
}
