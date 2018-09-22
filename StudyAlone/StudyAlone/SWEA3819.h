#pragma once
#include<iostream>

using namespace std;

int dp[200000], arr[200000];
int n;

int SWEA3819() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;
		int max = -0x7fffffff;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			max = max < arr[i] ? arr[i] : max;
		}

		int sum = arr[0];
		for (int i = 1; i < n; i++) {
			if (sum + arr[i] > 0) {
				sum += arr[i];
				max = max < sum ? sum : max;

			}
			else {
				sum = 0;
			}

		}
		cout << '#' << tc << ' ' << max << '\n';
	}

	return 0;
}
