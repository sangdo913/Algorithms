//https://www.acmicpc.net/problem/2210
//BOJ 2210 숫자판 점프
#pragma once
#include<iostream>

using namespace std;

int nums[5][5];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

bool check[1000000];
int ans = 0;

void dfs(int r, int c, int cnt, int num) {
	if (cnt == 6) {
		if (check[num]) return;
		check[num] = true;
		ans++;
		return;
	}

	num *= 10;
	num += nums[r][c];
	for (int d = 0; d < 4; d++) {
		int next[2] = { r + dr[d], c + dc[d] };
		if (next[0] < 0 || next[0] == 5 || next[1] < 0 || next[1] == 5) continue;

		dfs(next[0], next[1], cnt + 1, num);
	}
}
int BOJ2210() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> nums[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) dfs(i, j, 0, 0);
	}

	cout << ans;
	
	return 0;
}
