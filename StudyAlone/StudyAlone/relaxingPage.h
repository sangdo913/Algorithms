#pragma once
#include<cstdio>

int relaxingPage() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		int n, s, j, k;
		int res = 0;
		scanf("%d %d %d %d\n", &n, &s, &j, &k);
		
		j++;
		while (k--) {
			int in;
			scanf("%d\n",  &in);
		
			res += (in >= s) &&( (in - s) % j == 0);
		}
		printf("#%d %d\n", tc, res);
	}
	return 0;
}