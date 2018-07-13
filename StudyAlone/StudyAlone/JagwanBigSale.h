#pragma once
#include<cstring>
#include<cstdio>

int len, price[100000], temp[100000];

void mergeSort(int left, int m, int right) {
	int l = left, r = m + 1, k = l;

	while (l <= m && r <= right) {
		if (price[l] > price[r]) {
			temp[k++] = price[l++];
		}
		else {
			temp[k++] = price[r++];
		}
	}

	while (l <= m) temp[k++] = price[l++];
	while (r <= right) temp[k++] = price[r++];

	for (int i = left; i <= right; i++) {
		price[i] = temp[i];
	}
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;

		merge(l, m);
		merge(m + 1, r);

		mergeSort(l, m, r);
	}
}

int JagwanBigSale() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d\n", &len);

		long long sum = 0;

		for (int i = 0; i < len; i++) {
			scanf("%d \n", &price[i]);
			sum += (long long)price[i];
		}

		merge(0, len - 1);

		//3번째 마다의 물건 가격을 빼준다.
		for (int i = 2; i < len; i += 3) {
			sum -= (long long)price[i];
		}
		printf("#%d %lld\n", tc, sum);
	}

	return 0;
}