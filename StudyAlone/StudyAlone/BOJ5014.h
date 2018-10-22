//https://www.acmicpc.net/problem/5014
//BOJ 5014 스타트링크
#pragma once
#include<iostream>
#include<queue>

using namespace std;

queue<int> que;
bool visit[1000001];

int f, s, g, u, d;
int bfs() {
	que.push(s);

	int ti = 0;
	while (que.size()) {
		int cnt = que.size();

		while (cnt--) {
			int now = que.front(); que.pop();
			if (now == g) return ti;

			int next = now + u;
			if (next <= f&&!visit[next]) visit[next] = true, que.push(next);
			next = now - d;
			if (next > 0 && !visit[next]) visit[next] = true, que.push(next);
		}

		ti++;
	}
	return -1;
}

int BOJ5014() {
	cin >> f >> s >> g >> u >> d;

	int res = bfs();

	if (res == -1) cout << "use the stairs";
	else cout << res;
	return 0;
}