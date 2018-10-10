//https://www.acmicpc.net/problem/13460
//BOJ 13460 ±∏ΩΩ≈ª√‚2
#pragma once
#include<iostream>
#include<queue>

using namespace std;
char map[10][11];
int m, n;

struct COD {
	int br, bc;
	int rr, rc;
};

COD st;
bool visit[10][10][10][10];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int bfs() {
	queue<COD> que;
	que.push(st);
	visit[st.br][st.bc][st.rr][st.rc] = true;
	int time = 0;
	bool escape = false;

	que.push(st);

	while (que.size()) {
		int cnt = que.size();

		while (cnt--) {
			COD now = que.front();
			que.pop();

			if (map[now.rr][now.rc] == 'O') { escape = true; break; }

			for (int d = 0; d < 4; d++) {
				bool out[2] = { false,false };
				int t[2] = {};
				int p[2][2] = { { now.br, now.bc }, {now.rr, now.rc} };

				for (int i = 0; i < 2; i++) {
					while(map[p[i][0]+dr[d]][p[i][1]+dc[d]] !='#'){
						t[i]++;
						p[i][0] = p[i][0] + dr[d];
						p[i][1] = p[i][1] + dc[d];
						if (map[p[i][0]][p[i][1]] == 'O') break;
					}
					out[i] = map[p[i][0]][p[i][1]] == 'O';
				}

				if (out[0]) continue;
				
				if (p[0][0] == p[1][0] && p[0][1] == p[1][1]) {
					if (t[0] > t[1]) p[0][0] -= dr[d], p[0][1] -= dc[d];
					else p[1][0] -= dr[d], p[1][1] -= dc[d];
				}
				
				if (visit[p[0][0]][p[0][1]][p[1][0]][p[1][1]]) continue;
				visit[p[0][0]][p[0][1]][p[1][0]][p[1][1]] = true;
				
				COD next = { p[0][0], p[0][1], p[1][0], p[1][1] };
				que.push(next);
			}
		}
		if (escape) break;
		time++;

		if (time > 10) break;
	}
	return escape ? time : -1;
}

int BOJ13460() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				st.rr = i;
				st.rc = j;
				map[i][j] = '.';
			}
			else if (map[i][j] == 'B') {
				st.br = i;
				st.bc = j;
				map[i][j] = '.';
			}
		}
	}

	cout << bfs();

	return 0;
}