#pragma once
#include<cstdio>
#include<cstring>
#include<algorithm>

int n, m, map[12][12] = { 0 };
bool visit[12][12];
int que[100000][2], f, r;
enum DIR { DOWN = 0, UP = 1, RIGHT = 2, LEFT = 3 };
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}


bool isCross(int r, int c) {
	bool ch[3] = { false };

	for (int d = 0; d < 4; d++) {
		ch[d & 2] |= map[r + dy[d]][c + dx[d]] != 1 && map[r + dy[d]][c + dx[d]] != -1;
	}

	return ch[0] && ch[2];
}

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

		//도착
		if (y == n && x == n) {
			can = true;
			break;
		}

		cnt--;

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (visit[ny][nx]) continue; // 이미 갔던곳
			if (map[ny][nx] == 0) continue; //  막힌곳
			if (map[ny][nx] == -1) continue; // 맵 밖

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


int main() {

	scanf("%d %d\n", &n, &m);
	memset(map, -1, sizeof(map));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d\n", &map[i][j]);
		}
	}

	int res = getTime();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (isCross(i, j)) continue; //교차로인 경우

			if (map[i][j] == 0 && m) {

				memset(visit, false, sizeof(visit));
				map[i][j] = m;
				res = min(res, getTime());
				map[i][j] = 0;
			}
		}
	}

	printf("%d\n", res);
	return 0;
}