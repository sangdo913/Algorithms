#pragma once
#include<cstdio>
#include<cstring>
const int Size = 1000000;
long long BIT[1000001];

void update(int i, int to) {
	while (i <= Size) {
		BIT[i] += to;
		i += i & -i;
	}
}

long long get(int to) {
	long long res = 0;
	while (to > 0) {
		res += BIT[to];
		to -= to & -to;
	}
	return res;
}

int CodeBattle080702() {
	int t;
	scanf("%d\n", &t);
	for (int i = 1; i <= Size; i+=2) {
		for (int j = 1; j <= Size / i; j++) {
			update(i*j, i);
		}
	}
	for (int tc = 1; tc <= t; tc++) {
		int from, to;
		scanf("%d %d\n", &from, &to);
		printf("#%d %lld\n", tc, get(to) - get(from - 1));
	}
	return 0;
}