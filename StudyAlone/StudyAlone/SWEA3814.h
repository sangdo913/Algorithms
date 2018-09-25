//SWEEA3814 
//평등주의
#pragma once
#include<iostream>
#include<cstring>
#include<tuple>
#include<algorithm>
#include<queue>
using namespace std;

int n, arr[100000], temp[100000],k;

bool parametric(int h) {
	long long cut = 0;

	memcpy(temp, arr, sizeof(arr));

	for (int i = 0; i < n-1; i++) {
		if (temp[i] + h < temp[i + 1]) {
			cut += temp[i + 1] - (temp[i] + h);
			temp[i + 1] = temp[i] + h;
		}
	}
	for (int i = n - 1; i > 0; i--) {
		if (temp[i] + h < temp[i - 1]) {
			cut += temp[i - 1] - (temp[i] + h);
			temp[i - 1] = temp[i] + h;
		}
	}

	return cut <= k;
}

int bs() {
	int r = 1000000000, l = 0;
	
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
int SWEA3814() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> k;

		for (int i = 0; i < n; i++) {
			cin >> arr[i];;
		}

		cout << '#' << tc << ' ' << bs() << '\n';
	}
	return 0;
}
