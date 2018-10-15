//https://www.acmicpc.net/problem/14442
//BOJ 14442 벽 부수고 이동하기 2
#pragma once
#include<iostream>
#include<queue>

using namespace std;

char info[1000][1001];
int visit[1000][1000];

int N, M, K;

struct COD {
	int r, c, k;
	COD() :r(0), c(0), k(0) {}
	COD(int r, int c, int k) :r(r), c(c), k(k) {}
};

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

queue<COD> que;

int bfs() {
	COD now(0,0,K);

	visit[now.r][now.c] |= 1 << K;
	que.push(now);

	int time = 1;

	while (que.size()) {
		int cnt = que.size();
		
		while (cnt--) {
			now = que.front(); que.pop();
			if (now.r == N - 1 && now.c == M - 1) {
				return time;
			}
			
			for (int d = 0; d < 4; d++) {
				COD next = now;
				next.r += dr[d];
				next.c += dc[d];

				if (next.r < 0 || next.c < 0 || next.r >= N || next.c >= M) continue;
				if ((visit[next.r][next.c] & (1 << next.k))) continue;
				visit[next.r][next.c] |= 1 << next.k;

				if (info[next.r][next.c] == '1') {
					if (next.k) {
							next.k--;
							que.push(next);
							continue;
					}
				}
				else {
					que.push(next);
				}
			}
		}
		time++;
	}

	return -1;
}

int BOJ14442() {
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		cin >> info[i];
	}

	cout << bfs();
	return 0;
}




