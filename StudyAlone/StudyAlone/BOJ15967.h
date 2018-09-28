//https://www.acmicpc.net/problem/15967
//BOJ15967 ¿¡¹ÙÄñ
#pragma once

#include<iostream>

using namespace std;

long long tree[7000000];
long long lazy[7000000];

void init(int node, int s, int e, int idx, int v) {
	if (s == e) {
		tree[node] = v;
		return;
	}

	int m = (s + e) / 2;

	if (idx <= m) init(node*2, s, m, idx, v);
	else init(node * 2 + 1, m + 1, e, idx, v);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void lazy_update(int node, int s, int e) {
	tree[node] += lazy[node] * (e - s + 1);

	if (s != e) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}

	lazy[node] = 0;
}

void update(int node, int s, int e, int l, int r, long long v) {
	lazy_update(node, s, e);

	if (e < l || r < s) return;

	else if (l <= s && e <= r) {
		tree[node] += v * (e - s + 1);

		if (s != e) {
			lazy[node * 2] += v;
			lazy[node * 2 + 1] += v;
		}

		return;
	}

	int m = (s + e) / 2;
	
	update(node * 2, s, m, l, r, v);
	update(node * 2 + 1, m + 1, e, l, r, v);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long sum(int node, int s, int e, int l, int r) {
	lazy_update(node, s, e);

	if (e < l || r < s) return 0;

	if (l <= s && e <= r) {
		return tree[node];
	}

	int m = (s + e) / 2;

	return sum(node * 2, s, m, l, r) + sum(node * 2 + 1, m + 1, e, l, r);
}

int BOJ15967() {
	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		long long in;
		cin >> in;
		init(1, 1, n, i, in);
	}

	int cnt = m + k;

	while (cnt--) {
		int comm;
		cin >> comm;

		int l, r, v;
		
		switch (comm) {
		case 1:
			cin >> l >> r;
			cout << sum(1, 1, n, l, r) << '\n';
			break;
		case 2:
			cin >> l >> r >> v;
			update(1, 1, n, l, r, v);
			break;
		}
	}

	return 0;
}