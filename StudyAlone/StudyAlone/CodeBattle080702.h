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
	update(1, 1);
	for (int i = 2; i <= Size; i++) {
		long long nums = 1;
		int j = 2;
		for (; j*j < i; j++) {
			if (i%j == 0) {
				if (j & 1) nums += j;

				if ((i / j) & 1) {
					nums += i / j;
				}
			}
		}
		nums += i & 1 ? i : 0;
		nums += j * j == i && j & 1 ? j : 0;
		update(i, nums);
	}
	for (int tc = 1; tc <= t; tc++) {
		int from, to;
		scanf("%d %d\n", &from, &to);
		printf("#%d %lld\n", tc, get(to) - get(from - 1));
	}
	return 0;
}