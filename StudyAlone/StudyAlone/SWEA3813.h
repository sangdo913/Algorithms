#pragma once
#include<queue>
#include<iostream>
#include<algorithm>
#include<functional>

using namespace std;

int arr[200001], n, k;
int blocks[200000];

bool parametric(int w) {
	int cnt = 0;
	priority_queue<int> pq;
	priority_queue<int> pq2;

	for (int i = 0; i <= n; i++) {
		if (arr[i] <= w) {
			cnt++;
		}
		else {
			pq.push(cnt);
			cnt = 0;
		}
	}

	for (int i = 0; i < k; i++) {
		if (pq.empty()) return false;

		int now = pq.top();
		pq.pop();

		if (now < blocks[i]) return false;

		now -= blocks[i];
		//while (i < k && blocks[i] <= now) {
		//	now -= blocks[i];
		//	i++;
		//}

		//i--;

		if (now) pq.push(now);
	}
	return true;
}

int bs() {
	int l = 0, r = 200000;

	while (l <= r) {
		int m = (l + r) / 2;

		if (parametric(m)) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return l;
}

int SWEA3813() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> k;
		for (int i = 0; i < n; i++) cin >> arr[i];
		for (int i = 0; i < k; i++) cin >> blocks[i];

		arr[n] = 0x3f3f3f3f;
		sort(blocks, blocks + k, greater<int>());

		int res = bs();
		cout << '#' << tc << ' ' << res << '\n';
	}

	return 0;
}