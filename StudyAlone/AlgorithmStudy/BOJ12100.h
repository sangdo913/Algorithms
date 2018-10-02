//https://www.acmicpc.net/problem/12100
// BOJ 12100 2048(easy)
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int map[20][20], n;
int dm[4] = { 1,-1,1,-1 };
int start[4] = { 0,1,0,1 };
int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int move(int d) {
	int que[20], s = 0, e = 0;
	int res = 0;

	if ((d & 2) == 0) {
		for (int j = 0; j < n; j++) {
			s =  e = 0;
			bool canpl = false;
			int r = start[d] * (n - 1);
			while (r >= 0 && r < n) {
				if (map[r][j]) {
					if (canpl && que[e-1] == map[r][j]) {
						canpl = false;
						que[e-1] <<= 1;
						map[r][j] = 0;
					}

					else {
						canpl = true;
						que[e++] = map[r][j];
						map[r][j] = 0;
					}
				}
				r += dm[d];
			}

			r = start[d] * (n - 1);

			while (s!=e) {
				map[r][j] = que[s++];
				res = MAX(res, map[r][j]);
				r += dm[d];
			}
		}
	}

	else {
		for (int i = 0; i < n; i++) {
			s = e = 0;
			bool canpl = false;
			int c = start[d] * (n - 1);

			while (c >= 0 && c < n) {
				if (map[i][c]) {
					if (canpl && que[e - 1] == map[i][c]) {
						canpl = false;
						que[e - 1] <<= 1;
						map[i][c] = 0;
					}
					else {
						canpl = true;
						que[e++] = map[i][c];
						map[i][c] = 0;
					}
				}
				c += dm[d];
			}
			
			c = start[d] * (n - 1);

			while (s!=e) {
				map[i][c] = que[s++];
				res = MAX(res, map[i][c]);
				c += dm[d];
			}
		}
	}
	return res;
}

int dfs(int depth, int dir, int max) {
	if (depth == 5) {
		return max;
	}

	int restore[20][20];

	memcpy(restore, map, sizeof(map));

	int num = 0;

	for (int i = 0; i < 4; i++) {
		num = MAX(num, dfs(depth + 1, i, move(i)));
		memcpy(map, restore, sizeof(map));
	}

	return num;
}

int BOJ12100() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	cout << dfs(0, 0, 0);
	return 0;
}