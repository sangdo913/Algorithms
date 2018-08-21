//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWL6HGz6Ai4DFAUY
//¹«ÀÎµµ Å»Ãâ
#pragma once
#include<stdio.h>

int cache[21][1 << 20][3];
int infos[21][3], n;

void swap(int &i1, int &i2) {
	int temp = i1;
	i1 = i2;
	i2 = temp;
}

int max(int i1, int i2) {
	return i1 < i2 ? i2 : i1;
}

int getLength(int now, int mode, int row, int col, int visit) {
	int &ret = cache[now][visit][mode];

	if (ret) return ret;

	for (int i = 1; i <= n; i++) {
		if (visit & (1 << (i - 1))) continue;
		int nv = visit | (1 << (i - 1));
		if (row >= infos[i][0] && col >= infos[i][1]) {
			ret = max(ret, infos[i][2] + getLength(i, 0, infos[i][0], infos[i][1], nv));
		}
		if (row >= infos[i][0] && col >= infos[i][2]) {
			ret = max(ret, infos[i][1] + getLength(i, 1, infos[i][0], infos[i][2], nv));
		}
		if (row >= infos[i][1] && col >= infos[i][2]) {
			ret = max(ret, infos[i][0] + getLength(i, 2, infos[i][1], infos[i][2], nv));
		}
	}
	return ret;
}

int SWEA4335() {
	int t;
	scanf("%d\n", &t);
	infos[0][2] = infos[0][0] = infos[0][1] = 0x3f3f3f3f;

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d\n", &n);
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j < 1 << (n - 1); j++) {
				for (int k = 0; k < 3; k++) cache[i][j][k] = 0;
			}
		}

		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d\n", &infos[i][0], &infos[i][1], &infos[i][2]);
			if (infos[i][0] > infos[i][1]) swap(infos[i][0], infos[i][1]);
			if (infos[i][1] > infos[i][2]) swap(infos[i][1], infos[i][2]);
			if (infos[i][0] > infos[i][1]) swap(infos[i][0], infos[i][1]);
		}

		printf("#%d %d\n", tc, getLength(0, 0, 0x3f3f3f3f, 0x3f3f3f3f, 0));
	}
	return 0;
}
