#pragma once
#include<iostream>
using namespace std;

int arr[20000];
int BOJ16162() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, a, d;
	cin >> n >> a >> d;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	int now = a;
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] == now) {
			cnt++;
			now +=  d;
		}
	}

	cout << cnt;
	return 0;
}
