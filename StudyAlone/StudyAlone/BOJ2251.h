//https://www.acmicpc.net/problem/2251
//BOJ 2251 π∞≈Î
#pragma once
#include<queue>
#include<iostream>
#include<cstring>

using namespace std;

bool visit[9000000];
priority_queue<int> pq;
queue<int> que;

int bottle[3];

void passing(int a, int v[3]) {
	for (int i = 0; i < 3; i++) {
		v[i] = a % 201;
		a /= 201;
	}
}

int makev(int v[3]) {
	int a = 0;
	for (int i = 0; i < 3; i++) {
		a *= 201;
		a += v[2 - i];
	}
	return a;
}

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

void fromto(int v[3], int f, int t) {
	int remain = bottle[t] - v[t];
	int vmove = MIN(v[f], remain);
	v[f] -= vmove;
	v[t] += vmove;
}

void push(int v[3]) {
	int h = makev(v);
	if (!visit[h]) {
		visit[h] = true;
		que.push(h);
	}
}

void set(int d[3], int v[3]) {
	memcpy(d, v, sizeof(int)* 3);
}

void bfs() {
	int value;
	int v[3] = { 0,0,bottle[2]};

	visit[makev(v)] = true;
	
	que.push(makev(v));

	while (que.size()) {
		int now = que.front(); que.pop();

		passing(now, v);
		if (v[0] == 0) pq.push(-v[2]);

		int next[3];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == j) continue;
				set(next, v);
				fromto(next, i, j);
				push(next);
			}
		}
	}
}

int BOJ2251() {
	for (int i = 0; i < 3; i++) cin >> bottle[i];
	bfs();

	while (pq.size()) {
		int now = pq.top(); pq.pop();
		cout << -now << ' ';
	}
	return 0;
}