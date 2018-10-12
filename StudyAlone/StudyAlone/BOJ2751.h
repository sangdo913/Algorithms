//https://www.acmicpc.net/problem/2751
//BOJ2751 수 정렬하기 2
#pragma once
#include<iostream>

using namespace std;

int arr[1000000];
int temp[1000000];

void merge(int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		int l = s, r = m + 1, k = l;
		
		merge(s, m);
		merge(m + 1, e);

		while (l <= m && r <= e) {
			temp[k++] = arr[l] > arr[r] ? arr[r++] : arr[l++];
		}

		while (l <= m) temp[k++] = arr[l++];
		while (r <= e) temp[k++] = arr[r++];

		for (int i = s; i <= e; i++) {
			arr[i] = temp[i];
		}
	}
}
int BOJ2751() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	merge(0, n - 1);
	for (int i = 0; i < n; i++) cout << arr[i] << '\n';

	return 0;
}
