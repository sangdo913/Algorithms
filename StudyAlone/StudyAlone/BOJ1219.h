#pragma once
#include<cstdio>
#define INF 98764321

int que[10000], m, n, st, dt;
int adj[100][100][2], alen[100];
int earn[100];
int check[100];
bool visit[100];

void dfs(int now, int e) {
	for (int i = 0; i < alen[now]; i++) {
		int next = adj[now][i][0];
		int cost = adj[now][i][1];

		if (visit[next] && check[next] != INF && check[next] < e - cost + earn[next]) {
			check[next] = INF;
			e = INF;
		}

		if (!visit[next]) {
			visit[next] = true;
			if(e != INF) check[next] =e - cost + earn[next] > check[next] ? e - cost + earn[next] : check[next];
			else check[next] = INF;

			dfs(next, e == INF ? INF : e - cost + earn[next]);
			
			visit[next] = false;
		}
	}
}

void makeINF(int st) {
	int f = 0, r = 0;

	que[r++] = st;
	visit[st] = true;

	while (f != r) {
		int now = que[f++];

		for (int i = 0; i < alen[now]; i++) {
			int next = adj[now][i][0];

			if (check[next] != INF) {
				check[next] = INF;
				visit[next] = true;
				que[r++] = next;
			}
		}
	}
}

int BOJ1219() {
	scanf("%d %d %d  %d\n", &n, &st, &dt, &m);
	for (int i = 0; i < n; i++) {
		check[i] = -INF;
	}
	while (m--) {
		int from, to, cost;
		scanf("%d %d %d\n", &from, &to, &cost);
		adj[from][alen[from]][0] = to;
		adj[from][alen[from]++][1] = cost;
	}

	for (int i = 0; i < n; i++) scanf("%d \n", &earn[i]);

	check[st] = earn[st];
	
	visit[st] = true;
	dfs(st, earn[st]);
	visit[st] = false;

	for (int i = 0; i < n; i++) {
		if (visit[i]) continue;
		if (check[i]!= INF) continue;

		makeINF(i);
	}
	if (check[dt] == -INF) {
		printf("gg\n"); 
		return 0;
	}
	else if (check[dt] == INF) {
		printf("Gee\n"); 
		return 0;
	}

	printf("%d\n", check[dt]);
	return 0;
}