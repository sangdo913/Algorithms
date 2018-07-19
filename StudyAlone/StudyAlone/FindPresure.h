#pragma once
#include<cstdio>
#include<cstring>
int t, n, m, k;
int adj[1001][10001];
int alen[1001];
int queue[10000], f, r;
bool visit[1001];
int findPath() {

	f = r = 0;
	queue[r++] = 1;
	int time = 0;
	int cnt = 1;
	while (f != r) {
		int now = queue[f++];
		cnt--;
		if (now == n) {
			return time <= k ? time : -1;
		}

		for (int i = 0; i < alen[now]; i++) {
			int next = adj[now][i];
			if (visit[next]) continue;
			visit[next] = true;

			queue[r++] = next;
		}

		if (cnt == 0) {
			cnt = r - f;
			time++;
		}
	}

	return -1;
}

int FindPresure() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d\n", &n, &m, &k);
		memset(alen, 0, sizeof(alen));
		memset(visit, false, sizeof(visit));

		while (m--) {
			int st, dt;
			scanf("%d %d\n", &st, &dt);
			adj[st][alen[st]++] = dt;
		}

		printf("#%d %d\n", tc, findPath());
	}
	return 0;
}