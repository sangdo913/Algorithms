//https://www.acmicpc.net/problem/10816
//BOJ10816 ����ī��2
#pragma once
#include<iostream>

using namespace std;

int arr[500000], temp[500000];

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		int s = l, e = m + 1, k = s;

		merge(l, m);
		merge(e, r);

		while (s <= m && e <= r) {
			temp[k++] = arr[s] < arr[e] ? arr[s++] : arr[e++];
		}

		while (s <= m) temp[k++] = arr[s++];
		while (e <= r) temp[k++] = arr[e++];

		for (int i = l; i <= r; i++) {
			arr[i] = temp[i];
		}
	}
}

int ub(int l, int r, int value) {
	while (l <= r) {
		int m = (l + r) / 2;
		if (arr[m] > value) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return r+1;
}

int lb(int l, int r, int value) {
	while (l <= r) {
		int m = (l + r) / 2;
		if (arr[m] >= value) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return r+1;

}
int BOJ10816() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n, m;
	cin >> n ;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	merge(0, n - 1);
	cin >> m;

	while (m--) {
		int num;
		cin >> num;

		int idx[2] = { lb(0,n - 1,num), ub(0,n - 1,num) };
		
		cout <<idx[1] - idx[0] << ' ';
	}

	return 0;
}
