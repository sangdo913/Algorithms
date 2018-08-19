#pragma once
#include<cstdio>

int Codeforce0818B() {
	long long n, q;

	scanf("%lld %lld\n", &n, &q);

	while (q--) {
		long long x, y;
		scanf("%lld %lld\n", &x, &y);

		x--; y--;
		
		long long cnt = x * n + y;
		bool check = (x+y)&1;
		cnt >>= 1;
		if (check) {
			printf("%lld\n", (n*n+1) / 2 + 1 + cnt);
		}
		else {
			printf("%lld\n", 1 + cnt);
		}
	}
	return 0;
}