//https://www.acmicpc.net/problem/2618
//BOJ 2618 °æÂûÂ÷
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<tuple>
#include<map>


using namespace std;

#pragma once
struct INFO {
	int r1, c1, r2, c2, dist, next;
	INFO() :r1(0), c1(0), r2(0), c2(0), dist(0),next(0) {}
	INFO(int r1, int c1, int r2, int c2) : r1(r1), c1(c1), c2(c2), r2(r2), dist(0), next(0) {}
};

struct COD {
	int r, c, dist;
	COD() : r(0), c(0) {}
	COD(int r, int c) :r(r), c(c) {}
}cods[1001];

struct cmp {
	bool operator() ( INFO i1,  INFO i2) {
		return i1.dist > i2.dist;
	}
};

priority_queue<INFO, vector<INFO>, cmp> pq;

int n,w;
map<tuple<int, int, int>,COD > mp;

bool isout(int r, int c) {
	return r < 1 || c < 1 || r> n || c > n;
}

int ABS(int i1){
	return i1 > 0 ? i1 : -i1;
}

int getDist(const COD& a, const COD& b) {
	return  ABS(a.r - b.r) + ABS(a.c - b.c);
}

int pos[1001][1001];
int trace[1001][1001][2];
int st[1001], top;

void print(int p[2]) {
	int prev, idx;
	int cnt = w;

	while (p[0] || p[1]) {
		COD temp = mp[{p[0], p[1], w}];
		prev = temp.c;
		idx = temp.r;
		st[top++] = idx;
		p[idx - 1] = prev;
		w--;
	}
	while (top) {
		cout << st[--top] <<'\n';
	}
}

void dijk() {
	INFO now(1, 1, n, n);

	pq.push(now);

	while (pq.size()) {
		now = pq.top(); pq.pop();
		if (now.next == w) {
			int p[2] = { pos[now.r1][now.c1], pos[now.r2][now.c2] };
			cout << now.dist<<'\n';
			print(p);
			return;
		}
		INFO next = now;

		int prev = pos[next.r1][next.c1];

		next.next++;
		next.dist += getDist({ next.r1,next.c1 }, cods[next.next]);
		next.r1 = cods[next.next].r;
		next.c1 = cods[next.next].c;

		int p1 = pos[next.r1][next.c1];
		int p2 = pos[next.r2][next.c2];

		if (mp[{p1, p2, next.next}].r == 0 || mp[{p1, p2, next.next}) {
			mp[{p1, p2, next.next}] = COD(1, prev);
			pq.push(next);
		}

		next = now;

		prev = pos[next.r2][next.c2];

		next.next++;
		next.dist += getDist({ next.r2,next.c2 }, cods[next.next]);
		next.r2 = cods[next.next].r;
		next.c2 = cods[next.next].c;

		p1 = pos[next.r1][next.c1];
		p2 = pos[next.r2][next.c2];

		if (mp[{p1, p2, next.next}].r == 0){
			mp[{p1, p2, next.next}] = COD(2, prev);
			pq.push(next);
		}
	}
}

int BOJ2618() {

	cin >> n >> w;
	pos[1][1] = pos[n][n] = 0;

	for(int i = 1; i <= w; i++){
		cin >> cods[i].r >> cods[i].c;
		pos[cods[i].r][cods[i].c] = i;
	}

	 dijk();

	return 0;
}
