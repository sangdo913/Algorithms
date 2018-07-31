#pragma once
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;
struct ROAD {
	int to;
	int cost;
};

int p[100001][3][40], f, r, depth[100001];;
ROAD que[100001];
vector<ROAD> adj[100001];

int getLog(int i) {
	int res = 0;
	while (i) {
		res++;
		i >>= 1;
	}
	return res;
}

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}
int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int BOJ3176(){
	int n;
	scanf("%d\n", &n);

	for (int i = 1; i < n; i++) {
		int from, to, c;

		scanf("%d %d %d\n", &from, &to, &c);
		adj[from].push_back({ to,c });
		adj[to].push_back({ from,c });
	}

	memset(p, -1, sizeof(p));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 20; j++) p[i][1][j] = 987654321;
	}
	que[r++] = { 1,0 };
	p[1][0][0] = -2;
	while (f != r) {
		ROAD now = que[f++];

		for (int i = 0; i < adj[now.to].size(); i++) {
			ROAD nr = adj[now.to][i];
			int next = nr.to;

			if (p[next][0][0] == -1) {
				p[next][0][0] = now.to;
				p[next][1][0] = nr.cost;
				p[next][2][0] = nr.cost;

				depth[next] = depth[now.to] + 1;
				
				int ac = p[next][0][0];
				int l = 1;
				while (ac > 0) {
					p[next][0][l] = p[ac][0][l - 1];
					p[next][1][l] = min(p[next][1][l - 1], p[ac][1][l - 1]);
					p[next][2][l] = max(p[next][2][l - 1], p[ac][2][l - 1]);
					ac = p[ac][0][l - 1];
					l++;
				}
				que[r++] = nr;
			}
		}
	}

	int m;
	scanf("%d\n", &m);
	while (m--) {
		int i1, i2;
		scanf("%d %d\n", &i1, &i2);

		int d1 = depth[i1], d2 = depth[i2];
		if (d1 < d2) {
			int temp = i1;
			i1 = i2;
			i2 = temp;

			temp = d1;
			d1 = d2;
			d2 = temp;
		}

		int diff = d1 - d2;
		int res[2] = { 98764321, -1 };
		int ti1 = i1,i = 0;

		while (diff) {
			if (diff & 1) {
				res[0] = min(res[0], p[ti1][1][i]);
				res[1] = max(res[1], p[ti1][2][i]);
				ti1 = p[ti1][0][i];
			}
			i++;
			diff >>= 1;
		}

		int st = getLog(depth[ti1]);

		if (ti1 != i2) {
			for (int i = st; i >= 0; i--) {
				if (p[ti1][0][i] != p[i2][0][i]) {
					res[0] = min(res[0], p[ti1][1][i]);
					res[0] = min(res[0], p[i2][1][i]);

					res[1] = max(res[1], p[ti1][2][i]);
					res[1] = max(res[1], p[i2][2][i]);

					ti1 = p[ti1][0][i];
					i2 = p[i2][0][i];
				}
			}
			res[0] = min(res[0], p[ti1][1][0]);
			res[0] = min(res[0], p[i2][1][0]);

			res[1] = max(res[1], p[ti1][2][0]);
			res[1] = max(res[1], p[i2][2][0]);
		}

		printf("%d %d\n", res[0], res[1]);
	}
	return 0;
}