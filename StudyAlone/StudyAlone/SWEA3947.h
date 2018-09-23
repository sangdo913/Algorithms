//pro - SWEA3947
//가장 짧은 길 전부 청소하기
#pragma once
#include<algorithm>
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

int n, m, tc;

long long path[200001];
vector<int> adj[200001];
vector<int> cost[200001];
long long dist[200001];
long long INF = 0x7fffffffffffffff;

int visit[200001];

struct cmp {
	bool operator()(pair<int, int> i1, pair<int, int> i2) {
		return cost[i1.first][i1.second] < cost[i2.first][i2.second];
	}
};
void dijk() {
	for (int i = 2; i <= n; i++) {
		path[i] = dist[i] = INF;
	}

	dist[1] = 0;

	int st = 1;

	priority_queue<pair<long long, int> > pq;
	pq.push({ 0,st });

	int cnt = 0;

	while (cnt != n) {
		int now = pq.top().second;
		pq.pop();

		if (visit[now] == tc) continue;
		visit[now] = tc;
		cnt++;

		for (int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i];
			
			if (dist[next] > dist[now] + cost[now][i]) {
				dist[next] = dist[now] + cost[now][i];
				pq.push({ -dist[next], next });
				path[next] = cost[now][i];
				continue;
			}
			else if (dist[next] < dist[now] + cost[now][i]) {
				continue;
			}

			path[next] = cost[now][i] < path[next] ? cost[now][i] : path[next];
		}
	}
}

int SWEA3947() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;
	for ( tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		for (int i = 0; i < m; i++) {
			int f, t, c;
			cin >> f >> t >> c;

			adj[f].push_back(t);
			cost[f].push_back(c);

			adj[t].push_back(f);
			cost[t].push_back(c);
		}

		dijk();

		long long res = 0;
		for (int i = 2; i <= n; i++) {
			res += path[i];
		}

		cout << '#' << tc << ' ' << res << endl;
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			cost[i].clear();
		}
	}
	return 0;
}