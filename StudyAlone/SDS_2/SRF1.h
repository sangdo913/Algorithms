#pragma once
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

char n[30][30];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

struct COD {
	int r, c;
};

struct square {
	COD lu, rd;
};

bool check(int l , int r, int u , int d) {
	bool check[30][30] = {};
	int bnum = 0;
	char blocks[2];
	int bnums[2] = { 0,0 };

	for (int i = u; i <= d; i++) {
		for (int j = l; j <= r; j++) {
			if (check[i][j]) continue;
			bool ch = false;

			for (int cnt = 0; cnt < bnum; cnt++) {
				if (blocks[cnt] == n[i][j]) { ch = true; bnums[cnt]++; break; }
			}
			if (!ch) {
				if (bnum == 2) return false;
				else { blocks[bnum] = n[i][j]; bnums[bnum] = 1; bnum++; }
			}
			
			queue<COD> que;
			check[i][j] = true;
			que.push({ i,j });

			while (que.size()) {
				COD now = que.front(); que.pop();

				for (int dir = 0; dir < 4; dir++) {
					COD next;
					next.r = now.r + dr[dir];
					next.c = now.c + dc[dir];
					if (next.c < l || next.c > r || next.r < u || next.r > d) continue;
					else if (n[next.r][next.c] != n[i][j]) continue;
					else if (check[next.r][next.c]) continue;

					check[next.r][next.c] = true;
					que.push(next);
				}
			}
		}
	}
	return ((bnums[0] == 1 && bnums[1] >= 2) || (bnums[0] >= 2 && bnums[1] == 1));
}

bool fold(const square& s1, const square& s2) {
	return s1.lu.r >= s2.lu.r &&s1.lu.c >= s2.lu.c && s1.rd.r <= s2.rd.r && s1.rd.c <= s2.rd.c;
}

int DO() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int num;
		cin >> num;

		for (int i = 0; i < num; i++) {
			cin >> n[i];
		}
		vector<square> vec;
		vec.clear();

		int l, r, u, d;
		for (int l = 0; l < num; l++) {
			for (int r = l; r < num; r++) {
				for (int u = 0; u < num; u++) {
					for (int d = u; d < num; d++) {
						if (check(l, r, u, d)) {
							vec.push_back({ {u,l},{d,r} });
						}
					}
				}
			}
		}

		int res = 0;

		int x = 0;
		for (int i = 0; i < vec.size(); i++) {
			bool isfold = false;

			for (int j = 0; j < vec.size(); j++) {
				if (i == j) continue;
				isfold |= fold(vec[i], vec[j]);
			}

			res += !isfold;
		}

		cout << "Case #" << tc << '\n' << res << '\n';
	}

	return 0;
}
