#pragma once
#include<cstdio>
#include<cstring>

int memoi[11][1 << 10];
int n, m;
int adj[11][11];
int alen[11];

int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int findLongest(int now, int visit) {
	if (visit == (1 << n) - 1) {
		return 0;
	}

	int& ret = memoi[now][visit];
	if (ret != -1) return ret;

	ret = 0;

	for (int i = 0; i < alen[now]; i++) {
		int next = adj[now][i] - 1;
		if (visit & (1 << next)) continue;

		int nv = visit | (1 << next);
		ret = max(ret, findLongest(next + 1, nv) + 1);
	}

	return ret;
}


int LongestPath(){
	int T;
	scanf("%d\n", &T);

	for (int tc = 1; tc <= T; tc++){
		memset(alen, 0, sizeof(alen));
		memset(memoi, -1, sizeof(memoi));

		scanf("%d %d\n", &n, &m);

		while (m--) {
			int from, to;
			scanf("%d %d\n", &from, &to);

			adj[from][alen[from]++] = to;
			adj[to][alen[to]++] = from;
		}

		alen[0] = n;
		for (int i = 0; i < alen[0]; i++) adj[0][i] = i + 1;

		int res = findLongest(0, 0);
		printf("#%d %d\n", tc, res);
	}
	return 0;
}