#pragma once
#include<cstring>
#include<cstdio>
int cache[201];
int prices[20], money;
int favor[20];

int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int SUSHI() {
	int t;
	scanf("%d\n", &t);

	while (t--) {
		int n;

		scanf("%d %d\n", &n, &money);
		money /= 100;

		for (int i = 0; i < n; i++) {
			scanf("%d %d\n", &prices[i], &favor[i]);
			prices[i] /= 100;
		}
		memset(cache, 0, sizeof(cache));

		for (int i = 0; i < money; i++) {
			for (int j = 0; j < n; j++) {
				int nni = (i + prices[j]) % 201;
				int ni = i % 201;
				//슬라이딩 윈도우
				cache[nni] = max(cache[ni] + favor[j] , cache[nni]);
			}
		}

		printf("%d\n", cache[money % 201]);
	}
	return 0;
}