//줄세우기
#pragma once
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int que[50001], inorder[50001];
vector<int> adj[50001];
int n, m;

int SWEA3952() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++) adj[i].clear();
		memset(inorder, 0, sizeof(inorder));
		
		while (m--) {
			int front, rear;
			cin >>front  >> rear;
		
			adj[front].push_back(rear);
			inorder[rear]++;
		}

		int f = 0, r = 0;

		for (int i = 1; i <= n; i++) {
			if (inorder[i] == 0) {
				que[r++] = i;
			}
		}

		cout << '#' << tc;
		while (f != r) {
			int now = que[f++];

			cout << ' ' << now;

			for (int i = 0; i < adj[now].size(); i++) {
				int next = adj[now][i];


				inorder[next]--;

				if (inorder[next] == 0) {
					que[r++] = next;
				}
			}
		}
		cout << '\n';

	}
	return 0;
}