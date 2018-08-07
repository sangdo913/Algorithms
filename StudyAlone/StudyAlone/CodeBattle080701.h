#pragma once
#include<cstdio>

int info[20][2];

int CodeBattle080701() {
	int n, cal, res = 0, t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d\n", &n, &cal);
		res = 0;
		for(int i = 0 ;i < n; i++) {
			scanf("%d %d\n", &info[i][0], &info[i][1]);
		}

		for (int i = 1; i < 1 << n; i++) {
			int temp = i, idx = 0, good = 0, tcal = 0;
			while (temp) {
				if (temp & 1) {
					good += info[idx][0];
					tcal += info[idx][1];
					if (tcal > cal) break;
				}
				idx++;
				temp >>= 1;
			}
			if (tcal <= cal) {
				res = res < good ? good : res;
			}
		}
		printf("#%d %d\n", tc, res);
	}
	

	return 0;
}