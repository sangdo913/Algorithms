#pragma once
#include<cstdio>
#include<cstring>

int GCD(int a, int b) {
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}

	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
int abs(int i1) {
	return i1 > 0 ? i1 : -i1;
}
bool map[4001][4001];
int cod[200][2];
int SWEA5170() {
	int t;
	
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		int n;
		memset(map, false, sizeof(map));
		scanf("%d\n", &n);
		int cnt = 0;

		for (int i = 0; i < n; i++) {
			scanf("%d %d\n", &cod[i][0], &cod[i][1]);
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int child = cod[i][0] - cod[j][0];
				int parent = cod[i][1] - cod[j][1];
				if (parent == 0) {
					cnt += !map[0][2000];
					map[0][2000] = true;
					continue;
				}
				if (child == 0) {
					cnt += !map[2000][0];
					map[2000][0] = true;
					continue;
				}
				int gcd = GCD(abs(child),abs(parent));
				if (((child ^ parent) & (1 << 31))) {
					child = -abs(child);
					parent = abs(parent);
				}
				else {
					child = abs(child);
					parent = abs(parent);
				}
				cnt += !map[child / gcd + 2000][parent / gcd + 2000];
				map[child / gcd + 2000][parent / gcd + 2000] = true;
			}
		}
		
		printf("#%d %d\n", tc, cnt);
	}
	return 0;
}
