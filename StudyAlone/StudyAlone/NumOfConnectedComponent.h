#pragma once
#include<cstdio>

int adj[1001][1001];
int ladj[1001], queue[1001], f, r;
bool visit[1001];

bool connect(int i) {
	f = r = 0;

	queue[r++] = i;
	visit[i] = true;

	while (r != f) {
		int now = queue[f++];
		
		for (int i = 0; i < ladj[now]; i++) {
			int next = adj[now][i];
			
			if (visit[next]) continue;
			visit[next] = true;

			queue[r++] = next;
		}
	}
	return true;
}

int NumOfConnectedComponent() {
	int n, m;
	scanf("%d %d\n", &n, &m);

	while (m--) {
		int from, to;
		scanf("%d %d\n", &from, &to);

		adj[from][ladj[from]++] = to;
		adj[to][ladj[to]++] = from;
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (visit[i]) continue;
		res += connect(i);
	}
	printf("%d\n", res);
	return 0;
}