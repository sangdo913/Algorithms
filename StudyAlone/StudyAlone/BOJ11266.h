//https://www.acmicpc.net/problem/11266
#pragma once
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

vector<int> adj[10001];
bool res[10001];
int visit[10001];
int order, resNum;
int reses[10001];

int getCut(int idx, int p) {
	int o = order++;
	int child = 0;
	visit[idx] = o;

	for (int i = 0; i < adj[idx].size(); i++) {
		int next = adj[idx][i];
		if (next == p) continue;

		if (visit[next]) {
			visit[idx] = visit[next] < visit[idx] ? visit[next] : visit[idx];
		}
		else {
			child++;
			int r = getCut(next, idx);
			if (p && r >= o) {
				res[idx] = true;
			}
			visit[idx] = r > visit[idx] ? visit[idx] : r;
		}
	}

	if (!p && child > 1) res[idx] = true;

	return visit[idx];
}

int BOJ11266() {
	int n, m;
	scanf("%d %d\n", &n, &m);

	for (int i = 0; i < m; i++) {
		int from, to;
		scanf("%d %d\n", &from, &to);

		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	for (int i = 1; i <= n; i++) {
		if (visit[i]) continue;
		order = 1;
		visit[i] = getCut(i, 0);
	}

	for (int i = 1; i <= n; i++) {
		if (res[i]) {
			reses[resNum++] = i;
		} 
	}
	printf("%d\n", resNum);
	for (int i = 0; i < resNum; i++) {
		printf("%d ", reses[i]);
	}
	printf("\n");
	return 0;
}