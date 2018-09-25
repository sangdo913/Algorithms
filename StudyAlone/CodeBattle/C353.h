#pragma once
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

vector<int> groups;
int inorder[1001];
int tails[1001];
int p[1001];
int to[1001];
int n;
int visit[1001];
int que[1000];

int fp(int i) {
	if (p[i] < 0) return i;
	return p[i] = fp(p[i]);
}

int MAX(int i1, int i2) { return i1 > i2 ? i1 : i2; }

void merge(int i1, int i2) {
	int p1 = fp(i1);
	int p2 = fp(i2);

	if (p2 < p1) {
		int temp = p1;
		p1 = p2;
		p2 = temp;
	}

	p[p1] += p[p2];
	p[p2] = p1;
}

int C353() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		memset(p, -1, sizeof(p));
		memset(tails, 0, sizeof(tails));
		memset(inorder, 0, sizeof(inorder));
		groups.clear();

		for (int i = 1; i <= n; i++) {
			cin >> to[i];
			inorder[to[i]]++;
		}

		int f, r;
		f = r = 0;
		for (int i = 1; i <= n; i++) {
			if (inorder[i] == 0) {
				que[r++] = i;
			}
		}

		while (f != r) {
			int now = que[f++];
			
			int next = to[now];
			inorder[next]--;

			tails[next] = MAX(tails[next], tails[now] + 1);

			if (inorder[next] == 0) {
				que[r++] = next;
			}
		}
		
		for (int i = 1; i <= n; i++) {
			if (visit[i] == tc) continue;
			if (inorder[i] == 0) continue;
			visit[i] = tc;
			groups.push_back(i);

			int temp = to[i];
			while (temp != i) {
				visit[temp] = tc;
				merge(i, temp);
				temp = to[temp];
			}
		}

		int max = 0;
		int twos = 0;
		for (int i = 0; i < groups.size(); i++) {
			int cnt = 0;
			int g = groups[i];
			if (-p[g] == 2) {
				cnt = tails[g] + tails[to[g]]+2;
				twos += cnt;
			}
			else {
				cnt = -p[g];
			}
			max = max < cnt ? cnt : max;
			max = max < twos ? twos : max;
		}
		cout << '#' << tc << ' ' << max << '\n';
	}
	return 0;
}