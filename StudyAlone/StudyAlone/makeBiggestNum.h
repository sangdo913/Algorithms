#pragma once
#include<cstdio>

int nums[100000], temp[100000];


void mergeSort(int left, int m, int right) {
	int l = left, k = left, r = m + 1;
	while (l <= m && r <= right) {
		temp[k++] = nums[l] > nums[r] ? nums[l++] : nums[r++];
	}
	while (l <= m) temp[k++] = nums[l++];
	while (r <= right) temp[k++] = nums[r++];
	for (int i = left; i <= right; i++) nums[i] = temp[i];
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, m, r);
	}
}

int makeBiggestNum() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		int n, pl, mi;
		scanf("%d %d %d\n", &n, &pl, &mi);

		for (int i = 0; i < n; i++) {
			scanf("%d \n", nums + i);
		}
		merge(1, n - 1);

		long long res = nums[0];
		int idx = 1;
		for (int i = 0; i < pl; i++) res += nums[idx++];
		for (int i = 0; i < mi; i++) res -= nums[idx++];
		printf("#%d %lld\n",tc, res);
	}
	return 0;
}