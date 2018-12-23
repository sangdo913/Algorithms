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

void move(int d) {
	int que[20], s = 0, e = 0;
	int res = 0;

	for (int j = 0; j < n; j++) {
		s = e = 0;
		bool canpl = false;
		int r = start[d] * (n - 1);
		while (r >= 0 && r < n) {
			int &nblock = d & 2 ? map[j][r] : map[r][j];
			if (nblock) {
				if (canpl && que[e - 1] == nblock) {
					canpl = false;
					que[e - 1] <<= 1;
					nblock = 0;
				}

				else {
					canpl = true;
					que[e++] = nblock;
					nblock = 0;
				}
			}
			r += dm[d];
		}
	}
}

int dfs(int depth, int dir) {
	if (depth == 5) {
		int max = 0;
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) max = MAX(map[i][j], max);

		return max;
	}

	int restore[20][20];

	memcpy(restore, map, sizeof(map));

	int num = 0;

	for (int i = 0; i < 4; i++) {
		move(i);
		num = MAX(num, dfs(depth + 1, i));
		memcpy(map, restore, sizeof(map));
	}

	return num;
}

int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	cout << dfs(0, 0);
	return 0;
}