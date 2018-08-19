#pragma once
#include<cstdio>
#define INF 98764321

int que[10000], m, n, st, dt;
int adj[100][100][2], alen[100];
int earn[100];
long long check[100], check2[100];
int edge[100][3];

void makeINF(int st) {
	int f = 0, r = 0;

	que[r++] = st;

	while (f != r) {
		int now = que[f++];

		for (int i = 0; i < alen[now]; i++) {
			int next = adj[now][i][0];

			if (check[next] != INF) {
				check[next] = INF;
				que[r++] = next;
			}
		}
	}
}

int BOJ1219() {
	scanf("%d %d %d  %d\n", &n, &st, &dt, &m);
	for (int i = 0; i < n; i++) {
		check[i] = -INF;
		check2[i] = -1;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d\n", &edge[i][0], &edge[i][1], &edge[i][2]);
		adj[edge[i][0]][alen[edge[i][0]]][0] = edge[i][1];
		adj[edge[i][0]][alen[edge[i][0]]++][1] = edge[i][2];
	}

	for (int i = 0; i < n; i++) scanf("%d \n", &earn[i]);

	check[st] = earn[st];

	bool update = true;
	int cnt = n;

	while (cnt-- && update) {
		update = false;

		for (int i = 0; i < m; i++) {
			int now[3] = { edge[i][0], edge[i][1], edge[i][2] };

			if (check[now[0]] == -INF) continue;

			if (check[now[0]] + earn[now[1]] - now[2] > check[now[1]]) {
				update = true;
				check2[now[1]] = cnt;
				check[now[1]] = check[now[0]] + earn[now[1]] - now[2];
			}

		}
	}

	if (update) {
		for (int i = 0; i < n; i++) {
			if (check2[i] != 0) continue;
			if (check[i] == INF) continue;
			makeINF(i);
		}
	}

	if (check[dt] == INF) {
		printf("Gee\n");
		return 0;
	}
	else if (check[dt] == -INF) {
		printf("gg\n");
		return 0;
	}

	printf("%d\n", check[dt]);
	return 0;
}