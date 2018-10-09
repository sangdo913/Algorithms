#pragma once
#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int mp[1001][1001], n;
int a[2], b[2], c[2];
int dr[8] = { -1,-1,-1,0,0,1,1,1 };
int dc[8] = { -1,0,1,-1,1,-1,0,1 };

void init() {
	mp[a[0]][a[1]] =-1;
	for (int d = 0; d < 8; d++) {
		int r = a[0], c = a[1];
		while (true) {
			if (r < 1 || r > n || c < 1 || c > n) {
				break;
			}
			r = r + dr[d];
			c = c + dc[d];
			mp[r][c] = -1;
		}
	}
}

bool bfs() {
	bool visit[1001][1001] = { false };
	visit[b[0]][b[1]] = true;

	queue<pair<int, int> > que;

	que.push({ b[0], b[1] });
	
	while (que.size()) {
		auto now = que.front();
		que.pop();
		if (now.first == c[0] && now.second == c[1]) {
			return true;
		}

		for (int d = 0; d < 8; d++) {
			auto next = now;
			next.first += dr[d];
			next.second += dc[d];

			if (mp[next.first][next.second] == -1) continue;
			if (next.first < 1 || next.first > n || next.second < 1 || next.second > n) continue;
			mp[next.first][next.second] = -1;
			que.push(next);
		}
	}
	return false;
}

int LyftLevel5A() {

	cin >> n;
	cin >> a[0] >> a[1];
	cin >> b[0] >> b[1];
	cin >> c[0] >> c[1];
	init();
	if (bfs()) {
		cout << "YES";
	}
	else cout << "NO";
	


	return 0;
}
