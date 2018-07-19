#pragma once
#include<cstdio>

int nums[100000], temp[100000];
int m, n;

void mergeSort(int left, int m, int right) {
	int l = left, k = left, r = m + 1;
	while (l <= m && r <= right) {
		temp[k++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
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

bool bs(int value) {
	int l = 0, r = n - 1;
	while (l <= r) {
		int m = (l + r) / 2;
		if (nums[m] == value) return true;
		else if (nums[m] < value) {
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}
	return false;
}

int FindNumber(){
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d \n", &nums[i]);
	}

	merge(0, n - 1);

	scanf("%d\n", &m);
	while (m--) {
		int in;
		scanf("%d\n", &in);
		printf("%d\n", bs(in));
	}
	return 0;
}