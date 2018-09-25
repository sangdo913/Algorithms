//https://www.acmicpc.net/problem/8895
//막대 배치
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int n, l, r;
long long dp[21][21][21];

int BOJ8895() {
	dp[1][1][1] = 1;
	for (int i = 2; i <= 20; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 1; k <= i; k++) {
				dp[i][j][k] = dp[i - 1][j][k] * (i - 2) + dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1];
			}
		}
	}

	int t;
	cin >> t;

	while (t--) {

		cin >> n >> l >> r;

		cout << dp[n][l][r] << '\n';
	}
	return 0;
}