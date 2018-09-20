//https://www.acmicpc.net/problem/2939
//택배 배달
#pragma once
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#include<tuple>

using namespace std;

int r, c;
int cnt;

int arr[2001][201];
int costs[2001][201];

typedef pair<int, int> pii;

pii pos = { 1,1 };

int rcost[2001];
int dist[2001][2][2001][2];

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int getTime(int dr, int dc) {

	int s1 = arr[pos.first][1];
	int s2 = arr[pos.first][c];

	int d[4] = { 0,0 };

	int j = pos.second;

	while (j > 1) {
		d[0] += costs[pos.first][j];
		j--;
	}

	j = pos.second;
	while (j < c) {
		d[1] += costs[pos.first][j];
		j++;
	}

	j = dc;
	while (j != 1) {
		d[2] += costs[dr][j];
		j--;
	}

	j = dc;
	while (j != c) {
		d[3] += costs[dr][j];
		j++;
	}


	int res = d[0] + dist[pos.first][0][dr][0]+ d[2] - costs[pos.first][pos.second];
	res = MIN(res, d[0] + dist[pos.first][0][dr][1] + d[3] - costs[pos.first][pos.second]);
	res = MIN(res, d[1] + dist[pos.first][1][dr][0] + d[2] - costs[pos.first][pos.second]);
	res = MIN(res, d[1] + dist[pos.first][1][dr][1] + d[3] - costs[pos.first][pos.second]);
	if (dr == pos.first) {
		int len = 0;
		int pl = dc > pos.second ? -1 : +1;

		while (dc != pos.second) len += costs[dr][dc], dc+=pl;
		res = MIN(len, res);
	}

	return res;
}


void getMinRow() {
	for (int i = 1; i <= r; i++) {
		dist[i][0][i][1] = dist[i][1][i][0] = rcost[i];

		int srcost = 0;
		for (int i2 = i + 1; i2 <= r; i2++) {
			srcost += costs[i2-1][1] + costs[i2-1][c];
			dist[i][0][i][1] = dist[i][1][i][0] = MIN(srcost + rcost[i2], dist[i][1][i][0]);
		}

		srcost = 0;

		for (int i2 = i - 1; i2 >= 1; i2--) {
			srcost += costs[i2 + 1][1] + costs[i2 + 1][c];
			dist[i][0][i][1] = dist[i][1][i][0] = MIN(dist[i][0][i][1], srcost + rcost[i2]);

		}
	}

}

void allCost() {
	for (int i = 1; i <= r; i++) {
		for (int col = 0; col < 2; col++) {
			for (int i2 = i + 1; i2 <= r; i2++) {
				for (int col2 = 0; col2 < 2; col2++) {
					dist[i2][col2][i][col] = dist[i][col][i2][col2] = MIN(dist[i][col][i2-1][0]+dist[i2][0][i2][col2], dist[i][col][i2-1][1] + dist[i2][1][i2][col2]);
				}
			}
		}
	}
}

int BOJ2939() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> r >> c;

	memset(dist, 0x3f, sizeof(dist));

	for (int i = 1; i <= r; i++) {

		for (int j = 1; j <= c; j++) {

			cin >> costs[i][j];
			rcost[i] += costs[i][j];
		}
	}

	int comm;
	cin >> comm;

	long long res = costs[1][1];
	for (int i = 1; i <= r; i++) {
		dist[i][0][i][0] = costs[i][1];
		dist[i][1][i][1] = costs[i][c];
	}
	getMinRow();
	allCost();
	while (comm--) {
		int cr, cc;
		cin >> cr >> cc;
		res += getTime(cr, cc);
		pos = { cr, cc };
	}

	cout << res << '\n';
	return 0;
}