//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo&categoryId=AWXRDL1aeugDFAUo&categoryType=CODE
//56분 컷 무선 충전
#pragma once
#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

vector<int> map[12][12];

int dr[5] = { 0,-1,0,1,0 };
int dc[5] = { 0,0,1,0,-1 };

int info[2][101];

int m, a;

struct pos {
	int r, c;
} p[2];

int bcs[9];

pos que[200];

struct COMP {
	bool operator()(int i, int j) {
		return bcs[i] > bcs[j];
	}
};

void bfs(pos p, int idx, int c) {
	bool visit[12][12] = {};

	int cnt = 0;

	visit[p.r][p.c] = true;
	map[p.r][p.c].push_back(idx);

	int f, r;
	f = r = 0;

	que[r++] = p;

	while (cnt < c) {
		int cnt2 = r - f;

		while (cnt2--) {
			pos now = que[f++];

			for (int d = 1; d < 5; d++) {
				pos next = { now.r + dr[d], now.c + dc[d] };
				
				if (next.r < 1 || next.r > 10 || next.c < 1 || next.c > 10) continue;
				if (visit[next.r][next.c]) continue;
				visit[next.r][next.c] = true;
				map[next.r][next.c].push_back(idx);

				que[r++] = next;
			}
		}

		cnt++;
	}
}

int getValue() {
	vector<int>& v1 = map[p[0].r][p[0].c];
	vector<int>& v2 = map[p[1].r][p[1].c];

	int res = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (v1[i] == v2[j]) continue;
			int sum = bcs[v1[i]] + bcs[v2[j]];
			res = res < sum ? sum : res;
		}
	}
	return res;
}

int SWEA5644() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		cin >> m >> a;

		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++)
			{
				map[i][j].clear();
				map[i][j].push_back(0);
				map[i][j].push_back(0);
			}
		}

		p[0].c = p[0].r = 1;
		p[1].c = p[1].r = 10;

		for (int i = 0; i < m; i++) {
			cin >> info[0][i];
		}
		for (int i = 0; i < m; i++) {
			cin >> info[1][i];
		}

		int idx = 1;
		for (int i = 0; i < a; i++) {
			int r, c, range, ch;
			cin >> c >> r >>  range >> ch;
			bcs[idx] = ch;
			
			bfs({ r,c }, idx, range);
			idx++;
		}
		
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				sort(map[i][j].begin(), map[i][j].end(), COMP());
			}
		}

		int res = 0;
		for (int i = 0; i <= m; i++) {
			res += getValue();

			p[0].r += dr[info[0][i]];
			p[0].c += dc[info[0][i]];

			p[1].r += dr[info[1][i]];
			p[1].c += dc[info[1][i]];
		}

		cout << '#' << tc << ' ' << res << endl;
	}
	return 0;
}