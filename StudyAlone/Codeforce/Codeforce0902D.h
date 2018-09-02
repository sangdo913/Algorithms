#pragma once
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<int> adj[200001];
bool visit[200001];
int order[200001];

int Codeforce0902D() {
	int f, r;
	f = r = 0;
	int n;
	scanf("%d\n", &n);

	for (int i = 1; i < n; i++) {
		int from, to;
		scanf("%d %d\n", &from, &to);

		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	visit[1] = true;
	order[1] = 1;
	for (int i = 0; i < n; i++) {
		int in;
		scanf("%d \n", &in);
		order[in] = i;
	}
	
	queue<int> que;
	priority_queue<pair<int, int> > pq;
	que.push(1);
	visit[1] = true;

	int cnt = 0;
	while (que.size()) {
		int now = que.front();
		que.pop();

		if (order[now] != cnt++) {
			printf("No\n");
			return 0;
		}

		for (auto next : adj[now]) {
			if (visit[next]) continue;
			visit[next] = true;
			pq.push({ -order[next], next });
		}

		while (pq.size()) {
			int next = pq.top().second;
			pq.pop();

			que.push(next);
		}
	}
	printf("Yes\n");
	return 0;
}