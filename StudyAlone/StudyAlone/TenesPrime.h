#pragma once
#include<cstdio>
#include<cstring>

bool nprime[1000001];
int nums[10][1000001], len[10] = { 0 };

void setNum(int n) {
	int mem = n;
	bool cal[10] = { false };
	while (n) {
		if (!cal[n % 10])
		{
			cal[n % 10] = true;
			nums[n%10][len[n % 10]++] = mem;
		}

		n /= 10;
	}
}

int ubs(int d, int l, int r, int n) {
	int m;
	while (l <= r) {
		m = (l + r) / 2;

		if (nums[d][m] <= n) {
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}

	return l - 1 > 0 ? l - 1 : 0;
}

int lbs(int d, int l, int r, int n) {
	int m;
	while (l <= r) {
		m = (l + r) / 2;

		if (nums[d][m] < n) {
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}

	return r + 1 > len[d] ? len[d] : r + 1;
}

int TenesPrime() {
	int tc;
	scanf("%d\n", &tc);
	
	for (int i = 2; i <= int(1e6); i++) {
		for (int j = 2; i*j <= int(1e6); j++) { 
			nprime[i*j] = true;
		}
		if (nprime[i] == false) {
			setNum(i);
		}
	}

	for (int t = 1; t <= tc; t++) {
		int D, A, B;
		scanf("%d %d %d\n", &D, &A, &B);

		int l = lbs(D, 0, len[D] - 1, A);
		int r = ubs(D, 0, len[D] - 1, B);

		printf("#%d %d\n", t, r - l + 1);
	}
	return 0;
}