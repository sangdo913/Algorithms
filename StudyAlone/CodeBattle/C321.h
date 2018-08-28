#pragma once
#include<cstdio>
#include<cstring>
bool arr[101];

int C321() {
	int t;
	int n, k;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		memset(arr, false, sizeof(arr));

		scanf("%d %d\n", &n, &k);

		for (int i = 0; i < k; i++) {
			int in; scanf("%d\n", &in);

			arr[in] = true;
		}
		printf("#%d ", tc);

		for (int i = 1; i <= n; i++) {
			if (arr[i] == false) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	return 0;
}