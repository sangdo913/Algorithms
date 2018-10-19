//https://www.acmicpc.net/problem/2008
//BOJ 2008 사다리조작
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int dp[2][501];

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int BOJ2008() {
	int  t = 0;
	int n, m, a, b, x, y;
	memset(dp, 0x3f, sizeof(dp));

	cin >> n >> m >> a >> b >> x >> y;

	dp[0][a] = 0;

	int price = y;
	for (int i = 1; i <=n; i++) {
		if (a - i > 0) dp[0][a - i] = price;
		if (a + i <= n) dp[0][a + i] = price;
		price += y;
	}

	while (m--) {
		t++;
		int line;
		cin >> line;

		for (int i = 1; i <= n; i++) dp[t % 2][i] = dp[(t % 2) ^ 1][i];

		int now = t % 2;
		int prev = now ^ 1;
		dp[now][line] = MIN(dp[prev][line]+x, dp[prev][line+1]);
		dp[now][line+1] = MIN(dp[prev][line+1] + x, dp[prev][line]);

		price = dp[now][line+1] + y;
		for (int i = line+2; i <= n; i++) {
			dp[now][i] = MIN(dp[now][i], price);
			price += y;
		}

		price = dp[now][line] + y;
		for (int i = line-1; i >= 1; i--) {
			dp[now][i] = MIN(dp[now][i], price);
			price += y;
		}
	}
	cout << dp[t % 2][b];

	return 0;
}