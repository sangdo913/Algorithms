// https://codeforces.com/contest/1025/problem/B
//Weakened Common Divisor
#pragma once
#include<cstdio>

long long pa[150000][2],n;

long long GCD(long long a, long long b) {
	if(a < b){
		long long temp = a;
		a = b;
		b = temp;
	}

	while (b) {
		long long r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int Codeforce0819B() {
	scanf("%d\n", &n);
	scanf("%lld %lld\n", &pa[0][0], &pa[0][1]);

	long long lcm;

	long long gcd = GCD(pa[0][0], pa[0][1]);
	lcm = pa[0][0] * pa[0][1] / gcd;

	for (int i = 1; i < n; i++) {
		scanf("%lld %lld\n", &pa[i][0], &pa[i][1]);

		long long gcds[2] = { GCD(pa[i][0], lcm), GCD(pa[i][1], lcm) };
		gcd = GCD(gcds[0], gcds[1]);

		lcm = gcds[0]*gcds[1]/gcd;
		if (lcm == 1) {
			printf("-1\n");
			return 0;
		}
	}
	for (int i = 0; i < n; i++) {
		long long temp = GCD(lcm, pa[i][0]);
		if (temp == 1) {
			temp = GCD(lcm, pa[i][1]);
		}

		lcm = temp;
	}
	printf("%lld\n", lcm);
	return 0;
}