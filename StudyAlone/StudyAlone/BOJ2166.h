//https://www.acmicpc.net/submit/2166/9604055
#pragma once
#include<cstdio>

long long ccw(long long p1[2], long long p2[2], long long p3[2]) {
	return p1[0] * p2[1] + p2[0] * p3[1] + p3[0] * p1[1] - p2[0] * p1[1] - p3[0] * p2[1] - p1[0] * p3[1];
}

long long ABS(long long ll) {
	return ll > 0 ? ll : -ll;
}

int BOJ2166() {

	long long sp[2] , p[2][2] ;

	int n;
	scanf("%d\n", &n);
	n-=2;
	scanf("%lld %lld\n%lld %lld\n", &sp[0], &sp[1], &p[n%2][0], &p[n%2][1]);
	long long s = 0;
	
	while (n--) {
		scanf("%lld %lld", &p[n % 2][0], &p[n % 2][1]);
		s += ccw(sp, p[(n + 1) % 2], p[n % 2]);

	}

	printf("%.1lf\n", ABS(s) / 2.0);
	return 0;
}