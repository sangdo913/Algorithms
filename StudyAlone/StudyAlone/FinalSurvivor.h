#pragma once
#include<cstdio>

int map[12][12];

int dr[9] = { -1, -1, -1,0,0,0,1,1,1 };
int dc[9] = { -1,0,1,-1,0,1,-1,0,1 };

int FinalSurvivor() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);

		for (int i = 0; i <= n + 1; i++) {
			for (int j = 0; j <= n + 1; j++) map[i][j] = 4;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d \n", &map[i][j]);
			}
		}

		int num = 0;

		for (int i = 1; i <=n; i++) {
			for (int j = 1; j <= n; j++) {
				bool check[5] = { false };

				for (int d = 0; d < 9; d++) {
					check[map[i + dr[d]][j + dc[d]]] = true;
				}
					
				num += !check[0] && check[1] && check[2] && check[3];
				
			}
		}

		printf("#%d %d\n", tc, num);
	}
	return 0;
}