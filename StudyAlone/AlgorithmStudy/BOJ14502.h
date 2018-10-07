//https://www.acmicpc.net/problem/14502
//BOJ14502 ¿¬±¸¼Ò
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int n, m, map[8][8];
int wall;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int spread() {
	bool visit[8][8] = {};
	int que[100][2], s, e;

	s = e = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 2) {
				que[e][0]= i;
				que[e++][1] = j;

				visit[i][j] = true;
			}
		}
	}
	
	while (s != e) {
		int now[2] = { que[s][0], que[s++][1] };

		for (int d = 0; d < 4; d++) {
			int next[2] = { now[0] + dr[d], now[1] + dc[d] };
			
			if (next[0] < 0 || next[1] < 0 || next[0] >= n || next[1] >= m) continue;
			if (visit[next[0]][next[1]]) continue;
			if (map[next[0]][next[1]]) continue;
			visit[next[0]][next[1]] = true;
			
			que[e][0] = next[0];
			que[e++][1] = next[1];
		}
	}

	return n*m - e - wall - 3;
}

int MAX(int i1, int i2) {
	return i1 < i2 ? i2 : i1;
}

int choose(int cnt, int r, int c) {
	if (cnt == 3) {
		return spread();
	}

	if (r == n) return 0;
	
	int next[2] = { r, c + 1 };

	if (c + 1 == m) {
		next[0] = r + 1;
		next[1] = 0;
	}

	int res = choose(cnt, next[0], next[1]);

	if (map[r][c] == 0) {
		map[r][c] = 1;

		res = MAX(res, choose(cnt + 1, next[0], next[1]));

		map[r][c] = 0;
	}
	
	return res;
}

int BOJ14502() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) wall++;
		}
	}

	cout << choose(0, 0, 0);

	return 0;
}