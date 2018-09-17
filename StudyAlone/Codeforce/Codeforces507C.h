#pragma once
#include<cstdio>

long long arr[200000];
long long x[200000];
long long b[200000];
long long que[2000000];
int f, r;
int Codeforce507C() {
	int n; long long t;
	
	scanf("%d %lld\n", &n, &t);

	for (int i = 0; i < n; i++) {
		scanf("%lld ", &arr[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld \n", &x[i]);
	}

	for (int i = 0; i < n; i++) {
		if (x[i] < i + 1) {
			printf("No\n");
			return 0;
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (arr[i] + t > 3 * 1000000000000000000) {
			printf("No\n"); return 0;
		}
		que[r++] = arr[i] + t;
	}
	printf("Yes\n");
	while (f != r) {
		printf("%lld ", que[f++]);
	}
	return 0;
}
