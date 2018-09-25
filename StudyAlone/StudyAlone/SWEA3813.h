#pragma once
#include<queue>
#include<iostream>
#include<algorithm>
#include<functional>

using namespace std;

int arr[200001], n, k, sum;
int blocks[200000];
int temp[200000];
bool parametric(int w) {
	int cnt = 0;
	int idx = 0;
	int bsum = 0;
	int j = 0;
	for (int i = 0; i <= n; i++) {
		if (arr[i] <= w) {
			cnt++;
		}

		else {
			while (j < k && blocks[j] <= cnt) {
				cnt -= blocks[j];
				j++;
			}
			cnt = 0;
		}
	}

	return j == k;
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
		sum = 0;
		for (int i = 0; i < n; i++) cin >> arr[i];
		for (int i = 0; i < k; i++) cin >> blocks[i], sum +=blocks[i];

		arr[n] = 0x3f3f3f3f;

		int res = bs();
		cout << '#' << tc << ' ' << res << '\n';
	}

	return 0;
}