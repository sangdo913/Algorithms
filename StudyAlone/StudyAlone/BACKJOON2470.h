#pragma once
#include<cstdio>
const int INF = 2000000000;
int w[100000], temp[100000];

void mergeSort(int le, int m, int ri) {
	int l = le, r = m + 1, k = le;

	while (l <= m && r <= ri) {
		temp[k++] = w[l] < w[r] ? w[l++] : w[r++];
	}
	while (l <= m) temp[k++] = w[l++];
	while (r <= ri) temp[k++] = w[r++];
	for (int i = le; i <= ri; i++) w[i] = temp[i];
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);

		mergeSort(l, m, r);
	}
}

int bs(int l, int r, int value) {
	int m;
	while (l < r) {
		m = (l + r) / 2;
		if (value < w[m]) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	return r;
}

int abs(int i) {
	return i < 0 ? -i : i;
}

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

int BACKJOON2470() {
	int n;
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) scanf("%d \n", &w[i]);

	merge(0, n - 1);
	int res = INF;
	int idxes[2];
	for (int i = 0; i < n; i++) {
		int idx = bs(0, n - 1, -w[i]);
		int i1 ,i2;

		i1 = idx - 1;
		i2 = idx;
		while (i1 == i) i1--;
		while (i2 == i) i2++;

		int v1 = i1 < 0 ? INF : abs(w[i] + w[i1]);
		int v2 = i2 == n ? INF : abs(w[i]+ w[i2]);
		if (res > v1) {
			res = v1;
			idxes[0] = w[i];
			idxes[1] = w[i1];
		}
		if (res > v2) {
			res = v2;
			idxes[0] = w[i];
			idxes[1] = w[i2];
		}
	}
	if (idxes[0] > idxes[1]) {
		int temp = idxes[0];
		idxes[0] = idxes[1];
		idxes[1] = temp;
	}
	printf("%d %d\n", idxes[0], idxes[1]);
	return 0;
}