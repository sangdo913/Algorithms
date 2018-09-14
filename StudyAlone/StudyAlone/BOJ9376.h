//https://www.acmicpc.net/problem/9376
//Å»¿Á

#pragma once
#include<iostream>
#include<queue>
#include<cstring>

struct info {
	int r, c, num;
};
int h, w;
using namespace std;
queue<info> que;
typedef pair<int, int>  pii;
queue<pii> q2;

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }
const int INF = 0x3f3f3f3f;
int RES = INF;
int visit[3][102][102];
char map[102][102];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
bool isOut(int r, int c) {
	return r == 0 || r == h + 1 || c == 0 || c == w + 1;
}

int spread3() {
	queue<pii> temp;
	while (q2.size()) {
		temp.push(q2.front());
		q2.pop();
	}

	while (temp.size()) {
		pii now = temp.front();
		int num = visit[2][now.first][now.second];
		temp.pop();

		if (isOut(now.first, now.second)) {
			RES = MIN(RES, num);
			continue;
		}

		for (int d = 0; d < 4; d++) {
			pii next = { now.first + dr[d], now.second + dc[d] };
			if (visit[2][next.first][next.second] <= num) continue;
			if (map[next.first][next.second] == '*') continue;
			if (map[next.first][next.second] == '.') {
				visit[2][next.first][next.second] = num;
				temp.push(next);
			}
			else {
				if (visit[2][next.first][next.second] <= num + 1) continue;
				visit[2][next.first][next.second] = num + 1;
				q2.push(next);
			}
		}
	}

	return -1;
}
int pmin[2];

int spread() {
	queue<info> temp;
	while (que.size()) {
		temp.push(que.front());
		que.pop();
	}

	while (temp.size()) {
		info now = temp.front();
		temp.pop();
		int num = visit[now.num][now.r][now.c];

		if (isOut(now.r, now.c)) {
			pmin[now.num] = MIN(pmin[now.num], visit[now.num][now.r][now.c]);
			continue;
		}

		for (int d = 0; d < 4; d++) {
			info next = { now.r + dr[d], now.c + dc[d], now.num };

			if (map[next.r][next.c] == '*') continue;

			if (visit[now.num ^ 1][next.r][next.c] != INF) {
				int cnt = visit[now.num ^ 1][next.r][next.c] + num;
				if (visit[2][next.r][next.c] > cnt) {
					visit[2][next.r][next.c] = cnt;
					q2.push({ next.r,next.c });
				}
			}

			if (visit[next.num][next.r][next.c] <= num) continue;
			if (map[next.r][next.c] == '#') {
				if (visit[next.num][next.r][next.c] <= num + 1) continue;
				visit[next.num][next.r][next.c] = num + 1;
				que.push(next);
			}
			else {
				visit[next.num][next.r][next.c] = num;
				temp.push(next);
			}
		}
	}

	spread3();

	return -1;
}

int getTime() {
	int res = 0;

	while (que.size() || q2.size()) {
		res = spread();
	}
	RES = min(RES, pmin[0] + pmin[1]);
	return RES;
}

int BOJ9376() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		RES = INF;
		while (que.size()) que.pop();
		while (q2.size()) q2.pop();
		cin >> h >> w;
		int player = 0;

		memset(map, '.', sizeof(map));
		memset(visit, 0x3f, sizeof(visit));
		pmin[1] = pmin[0] = INF;

		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				cin >> map[i][j];
				if (map[i][j] == '$') {
					map[i][j] = '.';
					visit[player][i][j] = 0;
					que.push({ i,j,player++ });
				}
			}
		}

		cout << getTime() << '\n';
	}

	return 0;
}
