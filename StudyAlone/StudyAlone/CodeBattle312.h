#pragma once
#include<cstdio>
int h;
int que[100000], f, r, n;
int infos[100000][2];
int CodeBattle312() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d\n", &n, &h);
		f = r = 0;

		int rcnt = 0;
		
		for (int j = 0; j < 2; j++) {
			for(int i = 0; i < n; i++)
			scanf("%d \n", &infos[i][j]);
		}

		int height = infos[0][0];
		int res = infos[0][1] == 0;
		infos[0][1] = 1;
		rcnt = 1;
		que[r++] = 0;
		int idx = 1;
		while (idx != n) {
			if (height >= h) {
				int now = que[f++];
				height -= infos[now][0];
				rcnt -= infos[now][1];
			}

			while(idx != n && height < h) {
				que[r++] = idx;
				height += infos[idx][0];
				rcnt += infos[idx][1];
				idx++;
			}

			if (rcnt == 0) {
				res++;
				infos[que[r - 1]][1] = 1;
				rcnt = 1;
			}
		}

		while (r - f != 1) {
			int now = que[f++];
			if (infos[now][1]) {
				rcnt--;
				res += rcnt == 0;
			}
		}
		printf("#%d %d\n", tc, res);
	}
	return 0;
}