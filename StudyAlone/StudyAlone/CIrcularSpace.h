#pragma once
#include<cstdio>
int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}
int abs(int i1) {
	return i1 > 0 ? i1 : -i1;
}

int CircularSpace() {
	int t;
	scanf("%d\n", &t);
	int n, m, r1, r2, c1, c2;

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d %d %d %d\n", &n, &m, &r1, &c1, &r2, &c2);

		
		int moveR = min((n - abs(r1 - r2) ) % n, abs(r1 - r2));
		int moveC = min((m - abs(c1 - c2)) % m, abs(c1 - c2));
		printf("#%d %d\n", tc, moveR + moveC);
	}
	return 0;
}