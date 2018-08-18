// https://www.acmicpc.net/problem/14923
//πÃ∑Œ ≈ª√‚
#pragma once
#include<cstdio>

bool map[1002][1002];
int check[1002][1002][2];
int que[3000000][4], n, m;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

enum TYPE{X = 0, Y = 1, T = 2, M = 3};

int BOJ14923() {
	scanf("%d %d\n", &n, &m);

	int hx, hy, ex, ey;
	scanf("%d %d\n %d %d", &hy, &hx, &ey, &ex);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d \n", &map[i][j]);
			check[i][j][1] = check[i][j][0] = 98764321;
		}
	}
	int f = 0, r = 0;
	que[r][X] = hx;
	que[r][Y] = hy;
	que[r][M] = 1;
	que[r++][T] = 0;
	int D = -1;
	check[hy][hx][1] = 0;


	while (f != r) {
		int now[4] = { que[f][0], que[f][1], que[f][2], que[f++][3] };

		if (now[X] == ex && now[Y] == ey) {
			D = now[T];
			break;
		}

		for (int d = 0; d < 4; d++) {
			int nx = now[X] + dc[d];
			int ny = now[Y] + dr[d];
			
			if (map[ny][nx]) {
				if (now[M] && check[ny][nx][0] > now[T] ) {
					check[ny][nx][0] = now[T] ;
					que[r][X] = nx;
					que[r][Y] = ny;
					que[r][M] = 0;
					que[r++][T] = now[T] + 1;
				}
			}
			else {
				if (check[ny][nx][now[M]] > now[T]) {
					check[ny][nx][now[M]] = now[T];
						
					que[r][X] = nx;
					que[r][Y] = ny;
					que[r][M] = now[M];
					que[r++][T] = now[T] + 1;
				}
			}
		}
	}

	printf("%d\n", D);
	return 0;
}