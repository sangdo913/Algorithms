#pragma once
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int n, m, k, s;
bool visit[1000][1 << 10];
vector<int> se;
vector<int> vil;
int conv[1000];
vector<vector<int> > adj;

struct COD {
	int now, visit;
};

int res = 0;

int DO() {
	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		cin >> n >> m >> k >> s;
		s--;
		memset(visit, false, sizeof(visit));

		for (int i = 0; i < adj.size(); i++) {
			adj[i].clear();
		}
		se.clear();
		adj.clear();
		vil.clear();

		vil.resize(n);
		adj.resize(n);
		
		memset(conv, -1, sizeof(conv));

		for (int i = 0; i < k; i++)
		{
			int in;
			cin >> in;
			in--;
			conv[in] = se.size();
			se.push_back(in);
		}

		for (int i = 0; i < m; i++) {
			int from, to;
			cin >> from >> to;

			from--; to--;

			adj[from].push_back(to);
			adj[to].push_back(from);
		}
		queue<COD> que;
		visit[s][0] = true;

		que.push({ s,0 });

		res = 0;
		bool fin = false;

		while (true) {
			int cnt = que.size();
			while (cnt--) {
				COD now = que.front(); que.pop();

				if (now.now == s && now.visit == ((1 << k) - 1)) {
					fin = true;  break;
				}

				for (int i = 0; i < adj[now.now].size(); i++) {
					COD next;

					next.now = adj[now.now][i];
					next.visit = now.visit;
					if (conv[next.now] != -1) {
						next.visit |= 1 << conv[next.now];
					}

					if (visit[next.now][next.visit]) continue;
					visit[next.now][next.visit] = true;

					que.push(next);
				}
			}

			if (fin) break;
			
			res++;
		}

		cout << '#' << t << ' ' << res << '\n';
	}

	return 0;
}