//https://www.acmicpc.net/problem/5465
//∞ıµπ¿Ã
#pragma once
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

struct pii {
	int first,  second;
};
queue<pii> house, bear;
char map[802][803];
char temp[802][803];
int n, m;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
bool visit[802][802];

bool houseSpread() {
	int cnt = house.size();
	while (cnt-- ) {
		pii now = house.front();
		house.pop();

		for (int d = 0; d < 4; d++) {
			pii next = { now.first + dr[d], now.second + dc[d]};

			if (temp[next.first][next.second] == 'H') continue;
			if (temp[next.first][next.second] == 'M') return false;
			if (temp[next.first][next.second] != 'G') continue;
			temp[next.first][next.second] = 'H';
			house.push({ next.first, next.second });
		}
	}
	return true;
}

bool getTime(int st) {
	memset(visit, false, sizeof(visit));
	memcpy(temp, map, sizeof(map));

	while (house.size()) house.pop();
	while (bear.size()) bear.pop();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (temp[i][j] == 'M') bear.push({ i, j });
			else if (temp[i][j] == 'H') house.push({ i,j });
		}
	}
	
	int until = st;
	int t = 0;
	while (t != until && house.size()) {
		if(!houseSpread()) return false;
		t++;
	}
	temp[bear.front().first][bear.front().second] = 'G';

	while (bear.size()) {
		for (int i = 0; i < m; i++)
		{
			int cnt = bear.size();
			while (cnt--) {
				pii now = bear.front();
				bear.pop();
				if (temp[now.first][now.second] == 'H') continue;
				if (temp[now.first][now.second] == 'D') {
					return true;
				}

				for (int d = 0; d < 4; d++) {
					pii next = { now.first + dr[d], now.second + dc[d] };

					if (visit[next.first][next.second]) continue;
					if (temp[next.first][next.second] != 'G' && temp[next.first][next.second] != 'D') continue;
					visit[next.first][next.second] = true;

					bear.push(next);
				}
			}
		}
		houseSpread();
	}

	return false;
}

int bs() {
	int s = 0, e = 0x3f3f3f3f;

	while (s <= e) {
		int m = (s + e) / 2;

		if (getTime(m)) {
			s = m + 1;
		}
		else {
			e = m - 1;
		}
	}
	return s - 1;
}
int BOJ5465() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	memset(map, 'T', sizeof(map));
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
			cin >> map[i] + 1;
	}

	cout << bs() << '\n';
	return 0;
}
