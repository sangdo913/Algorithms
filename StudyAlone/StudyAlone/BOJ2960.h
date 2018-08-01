//https://www.acmicpc.net/problem/2960
#pragma once
#include<cstdio>

bool prime[1002];

int BOJ2960() {
	int cnt = 0;
	int n, k, res;
	scanf("%d %d\n", &n, &k);
	bool find = false;

	for (int i = 2; i <= n && !find; i++) {
		if (prime[i]) continue;

		for (int j = i; j <= n; j += i) {
			if (prime[j]) continue;
			prime[j] = true;
			cnt++;
			if (cnt == k) {
				res = j;
				find = true;
				break;
			}
		}
	}

	printf("%d\n", res);
	return 0;
}