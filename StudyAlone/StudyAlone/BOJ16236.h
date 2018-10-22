#pragma once
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int mm[20][20];
int n;
bool visit[20][20];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
bool isout(int r, int c) { return r < 0 || c < 0 || r >= n || c >= n; }

struct COD {
	int r, c, cnt;
	COD(int r, int c) : cnt(0), r(r), c(c){}
	COD() : r(0), c(0), cnt(0) {}
};

struct cmp {
	bool operator()(COD c1, COD c2) {
		if (c1.r == c2.r) { return c1.c > c2.c; }
		return c1.r > c2.r;
	}
};

struct FISH {
	COD p;
	int remain;
	int dist;
	int size;
	FISH() :p({ 0,0 }), size(2), remain(2),dist(0) {}

	void eat() {
		remain--;
		if (remain == 0) { size++; remain = size; }
	}
};

queue<COD> que;

bool ff(FISH &f) {
	COD now = f.p;

	memset(visit, false, sizeof(visit));
	visit[now.r][now.c] = true;
	que.push(now);

	priority_queue<COD, vector<COD>, cmp> pq;
	queue<COD> temp;
	que = temp;
	que.push(now);
	int cnt;
	bool isfind = false;

	while (!isfind && que.size()) {
		cnt = que.size();
		while (cnt--) {
			now = que.front(); que.pop();

			if (mm[now.r][now.c] && mm[now.r][now.c] < f.size) {
				isfind = true;
				pq.push(now);
				continue;
			}

			for (int d = 0; d < 4; d++) {
				COD next = now;
				next.r += dr[d];
				next.c += dc[d];
				next.cnt++;

				if (isout(next.r, next.c)) continue;
				if (visit[next.r][next.c]) continue;
				if (mm[next.r][next.c] > f.size) continue;
				visit[next.r][next.c] = true;
				que.push(next);
			}
		}
		if (isfind) break;
	}

	if (isfind == false) return false;

	now = pq.top(); pq.pop();
	f.p = now;
	f.p.cnt = 0;
	f.eat();
	f.dist += now.cnt;
	mm[now.r][now.c] = 0;
	return true;
}
int BOJ16236() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;

	FISH f;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> mm[i][j];
			if (mm[i][j] == 9) {
				f.p.r = i;
				f.p.c = j;
				//mm[i][j] = 0;
			}
		}
	}

	while (ff(f)) {}
	cout << f.dist;
	return 0;
}

