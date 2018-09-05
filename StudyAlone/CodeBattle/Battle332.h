//5521. 상원이의 생일파티
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int n, m;
int invite[501];
int adj[501][501], alen[501];
int que[500];

int Battle332() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		memset(invite, 0, sizeof(invite));
		memset(alen, 0, sizeof(alen));

		for (int i = 0; i < m; i++) {
			int from, to;
			cin >> from >> to;
			adj[from][alen[from]++] = to;
			adj[to][alen[to]++] = from;
		}

		int f, r;
		f = r = 0;
		que[r++] = 1;
		invite[1] = 1;
		int res = 0;

		while (f != r) {
			int now = que[f++];

			if (invite[now] == 3) break;
			for (int idx = 0; idx < alen[now]; idx++) {
				int next = adj[now][idx];

				if (invite[next]) continue;
				invite[next] = invite[now] + 1;
				res++;
				que[r++] = next;
			}
		}
		cout << '#' << tc << ' ' << res << '\n';
	}

	return 0;
}