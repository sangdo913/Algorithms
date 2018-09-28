//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo
//SWEA5653 줄기세포배양
#pragma once
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

bool map[700][700];
int n, m, k;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

struct CEPO {
	int r, c;
	int life;
};

bool operator<(const CEPO&c1, const CEPO&c2) {
	return c1.life < c2.life;
}

priority_queue< CEPO> pq[301];

int gen[700][700];
int life[700][700];

int SWEA5653() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> k;

		int res = 0;
		memset(map, false, sizeof(map));
		memset(gen, 0x3f, sizeof(gen));
		memset(life, 0, sizeof(life));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int in;
				cin >> in;
				if (in) {
					CEPO cepo = { i+300,j+300, in};
					pq[0].push(cepo);
				}
			}
		}

		for(int i = 0; i <= k; i++){
			while (pq[i].size()) {
				CEPO now = pq[i].top();
				pq[i].pop();

				if (map[now.r][now.c]) continue;
				map[now.r][now.c] = true;
			
				int dtime = i + now.life * 2;
				int ctime = i + now.life + 1;

				if (dtime > k)
				{
					res++;
				}

				CEPO next = now;

				if (ctime > k) continue;

				for (int d = 0; d < 4; d++) {
					next.r = now.r + dr[d];
					next.c = now.c + dc[d];
					
					if (gen[next.r][next.c] < ctime) {
						continue;
					}
					
					else if (gen[next.r][next.c] == ctime && life[next.r][next.c] >= now.life) {
						continue;
					}

					gen[next.r][next.c] = ctime;
					life[next.r][next.c] = now.life;

					if (ctime <= k) pq[ctime].push(next);
				}
			}
		}

		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}
