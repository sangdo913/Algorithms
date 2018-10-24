#pragma once
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

vector<int> adj[17];
int inorder[17];
long long fac[17];
int n, m, used;
bool visit[17];

long long cache[17];

long long dfs(int node, int len) {
	long long &res = cache[node];
	if (res != -1) return res;

	res = 0;
	for (int i = 0; i < adj[node].size(); i++) {
		int next = adj[node][i];
		res += dfs(next, len+1);
	}

	return res ? res : 1;
}
int C382() {
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= 16; i++) {
		fac[i] = fac[i - 1] * i;
	}

	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		memset(adj, false, sizeof(adj));
		memset(visit, false, sizeof(visit));
		memset(cache, -1, sizeof(cache));

		for (int i = 1; i < 17; i++) {
			adj[i].clear();
		}

		cin >> n >> m;
		while (m--) {
			int f, t;
			cin >> f >> t;

			inorder[t]++;
			adj[f].push_back(t);
		}

		long long res = 1;

		for (int i = 1; i <= n; i++) {
			if (inorder[i] == 0) {
				res *= dfs(i, 0);
			}
		}

		res *= fac[n - used];
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}
