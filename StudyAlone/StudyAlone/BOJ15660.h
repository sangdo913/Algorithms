//https://www.acmicpc.net/problem/status/15660
//BOJ 15660 테트로미노 2
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int blocks[19][3][2] = {
	{{0,1},{0,2},{0,3} },
	{{1,0},{2,0},{3,0}},
	{{1,0},{0,1},{1,1}},
	{{1,0},{2,0},{2,1}},
	{{0,1},{0,2},{1,0}},
	{{0,1},{1,1},{2,1}},
	{{1,0},{1,-1},{1,-2}},
	{{1,0},{2,0},{2,-1}},
	{{1,0},{1,1},{1,2}},
	{{0,-1},{1,-1},{2,-1}},
	{{0,1},{0,2},{1,2}},
	{{1,0},{1,-1},{0,1}},
	{{-1,0},{0,1},{1,1}},
	{{0,-1},{1,0},{1,1}},
	{{0,1},{1,0},{-1,1}},
	{{1,-1},{1,0},{1,1}},
	{{-1,-1},{0,-1},{1,-1}},
	{{-1,-1},{-1,0},{-1,1}},
	{{-1,1},{0,1},{1,1}}
};
int m, n;

const int INF = 100000;
int map[507][507];

struct COD {
	int x, y;
	COD(int x, int y) : x(x), y(y) {}
	COD() :x(0), y(0) {}
};
struct INFO {
	int v;
	COD p[4];
};

struct cmp {
	bool operator()(const INFO &i1, const INFO& i2) {
		return i1.v > i2.v;
	}
};

vector<INFO> bvec;

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

bool visit[507][507];

bool isfold(const INFO& i1, const INFO& i2) {
	for (int i = 0; i < 4; i++) {
		visit[i1.p[i].x][i1.p[i].y] = true;
	}
	bool res = false;
	for (int i = 0; i < 4; i++) {
		res |= visit[i2.p[i].x][i2.p[i].y];
	}

	for (int i = 0; i < 4; i++) {
		visit[i1.p[i].x][i1.p[i].y] = false;
	}
	return res;
}

int MAX(int i1, int i2) {
	return i1 < i2 ? i2 : i1;
}


int BOJ15660() {
	int n, m;
	for (int i = 0; i < 507; i++) {
		for (int j = 0; j < 507; j++) map[i][j] = -INF;
	}

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> map[i + 3][j + 3];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int b = 0; b < 19; b++) {
				INFO bl;
				bl.v = map[i+3][j+3]; 
				bl.p[3] = COD(i+3, j+3);
				for (int d = 0; d < 3; d++) {
					int p[2] = { 3 + i + blocks[b][d][0], 3 + j + blocks[b][d][1] };
					bl.p[d] = { p[0],p[1] };
					bl.v += map[p[0]][p[1]];
				}
				bvec.push_back(bl);
			}
		}
	}

	sort(bvec.begin(), bvec.end(), cmp());
	int res = 0;

	int until = MIN(bvec.size(), 150);
	int idxs[150];
	for (int i = 0; i < until; i++) {
		idxs[i] = i;
	}

	for (int i = 0; i < until; i++) {
		for (int j = i + 1; j < until; j++) {
			if (!isfold(bvec[i], bvec[j])) {
				res = MAX(res, bvec[i].v + bvec[j].v);
			}
		}
	}
	
	cout << res << endl;
	return 0;
}