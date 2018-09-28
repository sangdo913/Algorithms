//https://www.acmicpc.net/problem/10999
//BOJ 10999 구간 합 구하기2
#pragma once
#include<iostream>
using namespace std;

long long tree[4000000];
long long lazy[4000000];

int m, k, n;

void init(int node, int s, int e, int l, int r, int diff) {
	if (e < l || s > r) return;

	else if (s == e) {
		tree[node] = diff;
		return;
	}

	init(node * 2, s, (s + e) / 2, l, r, diff);
	init(node * 2 + 1, (s + e) / 2 + 1, e, l, r, diff);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void lazy_update(int node, int s, int e) {
	tree[node] += (e - s + 1)*lazy[node];

	if (s != e) {
		lazy[node * 2 + 1] += lazy[node];
		lazy[node * 2] += lazy[node];
	}

	lazy[node] = 0;
}

void update_range(int node, int s, int e, int l, int r, long long diff) {
	lazy_update(node, s, e);

	if (e < l || r < s) {
		return;
	}
	else if (l <= s && e <= r) {
		tree[node] += (e - s+1)*diff;

		if (s != e) {
			lazy[node * 2] += diff;
			lazy[node * 2 + 1] += diff;
		}
		return;
	}

	int m = (s + e) / 2;
	update_range(node * 2, s, m, l, r, diff);
	update_range(node * 2 + 1, m + 1, e, l, r, diff);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long sum(int node, int s, int e, int l, int r){
	lazy_update(node, s, e);

	if (e < l || r < s) return 0;

	else if (l <= s && e <= r) {
		return tree[node];
	}

	int m = (s + e) / 2;
	return sum(node * 2, s, m, l, r) + sum(node * 2 + 1, m + 1, e, l, r);
}

int BOJ10999() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		long long in;
		cin >> in;
		init(1, 1, n, i, i, in);
	}

	int cnt = m + k;
	int l, r, v;

	while (cnt--) {
		int comm;
		cin >> comm;
		switch (comm) {
		case 1:
			cin >> l >> r >> v;

			update_range(1, 1, n, l, r, v);

			break;
		case 2:
			cin >> l >> r;

			cout << sum(1, 1, n, l, r) << '\n';

			break;
		}
	}
	
	return 0;
}