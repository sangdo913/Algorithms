#pragma once
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

int r, c;
int cnt = 0;

int arr[2001][201];
typedef pair<int, int> pii;

pii pos = { 1,1 };

struct NODE {
	int pos[2], num, dist;
}nodes [6000];

vector<int> adj[6000];
vector<int> cost[6000];

int BOJ2939() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> r >> c;

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> nodes[cnt].dist;

			arr[i][j] = cnt;
			nodes[cnt].num = cnt;
			nodes[cnt].pos[0] = i;
			nodes[cnt].pos[1] = j;
			cnt++;
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
				int now = arr[i][j];
			if (j == 1 || j == c) {
				if (i - 1) {
					adj[now].push_back(arr[i - 1][j]);
					cost[now].push_back(nodes[now].dist);
				}
				else if (i != r) {
					adj[now].push_back(arr[i + 1][j]);
					cost[now].push_back(nodes[now].dist);
				}
			}

			if (j != 1) {
				adj[]
			}
			if (j != c) {

			}
		}
	}
	return 0;
}