//https://www.acmicpc.net/problem/1799
//BOJ 1799 ºñ¼ó
#pragma once
#include<iostream>

using namespace std;

int n;
int map[10][10];
int nums[10];

int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int dr[4] = { -1,1,-1,1 };
int dc[4] = { -1,1, 1, -1 };

bool dircheck(int r, int c, int flag) {
	bool cnt[2] = {};

	for (int d = 0; d < 4; d++) {
		for (int i = 1; i < n && cnt[d/2] == false; i++) {
			int next[2] = { r + i * dr[d], c + i * dc[d] };

			if (next[0] < 0 || next[1] < 0 || next[0] > n - 1 || next[1] > n - 1) break;

			if (map[next[0]][next[1]] == 1) {
				cnt[d / 2] = true;
			}
		}
	}

	if (cnt[0] + cnt[1] <= flag) {
		for (int d = 0; d < 4; d++) {
			for (int i = 1; i < n; i++) {
			int next[2] = { r + i * dr[d], c + i * dc[d] };

			if (next[0] < 0 || next[1] < 0 || next[0] > n - 1 || next[1] > n - 1) break;
				map[next[0]][next[1]] = 0;
			}
		}

		map[r][c] = 0;
	}

	
	return cnt[0] + cnt[1] <= flag;
}

int BOJ1799() {
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int res = 0;
	
	int flag = 0;
	
	while (flag < 3) {
		bool deleted = false;

		for (int i = 0; i < n && !deleted; i++) {
			for (int j = 0; j < n && !deleted; j++) {
				if (map[i][j]) {
					deleted = dircheck(i, j, flag);
					if (deleted) {
						flag = 0;
						res++; break;
					}
				}
			}
		}
		
		if (deleted == false) flag++;
	}

	cout << res;
	
	return 0;
}
