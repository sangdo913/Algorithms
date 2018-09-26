//SWEA3998
//Inversion Counting
#pragma once
#include<iostream>

using namespace std;

int arr[100000];
int temp[100000];

long long merge(int l, int r) {
	long long cnt = 0;
	if (l < r) {

		int m = (l + r) / 2;
		int s = l, e = m+1;
		
		cnt += merge(l, m);
		cnt += merge(m + 1, r);
		
		int k = s;

		while (s <= m && e <= r) {
			if (arr[s] <= arr[e]) {
				temp[k++] = arr[s++];
			}
			else {
				cnt += m + 1 - s;
				temp[k++] = arr[e++];
			}
		}

		while (s <= m) temp[k++] = arr[s++];
		while (e <= r) temp[k++] = arr[e++];

		for (int i = l; i <= r; i++) {
			arr[i] = temp[i];
		}
	}

	return cnt;
}

int SWEA3998() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		cout << '#' << tc << ' ' << merge(0, n - 1) << '\n';
	}
	return 0;
}
