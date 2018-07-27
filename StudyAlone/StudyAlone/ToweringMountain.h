#pragma once
#include<cstdio>
int st[2][50001];
int num[50001], n;
int top[2];
enum MODE{HIGH, LOW};

int ToweringMountain() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d \n", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d \n", &num[i]);
		}

		top[0] = top[1] = 0;
		int mode = HIGH;
		int res = 0;
		st[HIGH][top[0]++] = num[0];
		for (int i = 1; i < n; i++) {
			if (mode) {
				if (num[i - 1] <= num[i]){
					res += (top[0] - 1) * (top[1]);
					mode ^= 1;
					top[0] = 1;
					st[0][0] = st[1][--top[1]];
					top[1] = 0;
				}
			}
			else {
				if (num[i - 1] >= num[i]) {
					mode ^= 1;
					top[1] = 0;
				}
			}
			st[mode][top[mode]++] = num[i];
		}
		res += (top[0] - 1) * (top[1]);
		printf("#%d %d\n",tc, res);
	}
	return 0;
}