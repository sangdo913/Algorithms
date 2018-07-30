//https://www.acmicpc.net/problem/3020
#pragma once
#include<cstdio>

int idt[3000000];

int getParent(int i) {
	return i >> 1;
}

int getSTI(int i) {
	int res = 0;
	while (i) {
		res++; i >>= 1;
	}

	return (1 << res) - 1;
}

void update(int from, int to) {
	while (from <= to) {
		if (from % 2) {
			idt[from]++;
		}
		if ((to % 2) == 0) {
			idt[to]++;
		}
		from = (from + 1) / 2;
		to = (to - 1) / 2;
	}
}

int sum(int idx) {
	int sum = 0;
	while(idx) {
		sum += idt[idx];
		idx >>= 1;
	}
	return sum;
}

int BOJ3020() {
	int n, h;
	scanf("%d %d\n", &n, &h);

	int sti = getSTI(h), in;
	int res[2] = { 987654321, 0 };
	while (n--) {
		scanf("%d\n", &in);
		if (n % 2) {
			update(sti + 1, in + sti);
		}
		else {
			update(h - in + sti + 1, h + sti);
		}
	}

	for (int i = sti + 1; i <= h + sti; i++) {
		int cnt = sum(i);
		if (cnt < res[0]) {
			res[1] = 1;
			res[0] = cnt;
		}
		else if (cnt == res[0]) {
			res[1]++;
		}
	}
	printf("%d %d\n", res[0], res[1]);

	return 0;
}