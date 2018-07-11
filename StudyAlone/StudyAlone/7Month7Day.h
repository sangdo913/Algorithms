#pragma once
#include<cstdio>
#include<cstring>

int n, m, map[12][12] = { 0 };
bool visit[12][12];
int que[100000][2], f,r;

int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int getTime() {
	f = r = 0;
	int time = 1;
	bool can = false;

	que[r][0] = que[r][1] = 1;
	r++;
	visit[1][1] = true;

	int cnt = 1;
	
	while (f != r) {
		int x = que[f][0];
		int y = que[f++][1];

		//µµÂø
		if (y == n && x == n) {
			can = true;
			break;
		}

		cnt--;

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (visit[ny][nx]) continue; // ÀÌ¹Ì °¬´ø°÷
			if (map[ny][nx] == 0) continue; //  ¸·Èù°÷

			if (time % map[ny][nx] == 0) {
				que[r][0] = nx;
				que[r++][1] = ny;
				visit[ny][nx] = true;
			}
			else {
				que[r][0] = x;
				que[r++][1] = y;
			}
		}

		if (cnt == 0) {
			time++;
			cnt = r - f;
		}
	}

	return can ? --time : 987654321;
}

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

int SevenMonth7Day() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d\n", &n, &m);
		memset(map, 0, sizeof(map));

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d\n", &map[i][j]);
			}
		}

		int res = getTime();

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j] == 0) {

					memset(visit, false, sizeof(visit));
					map[i][j] = m;
					res = min(res, getTime());
					map[i][j] = 0;
				}
			}
		}

		printf("#%d %d\n", tc, res);
	}
	return 0;
}