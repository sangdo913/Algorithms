//https://www.acmicpc.net/problem/5623
//수열의 합
#pragma once
#include<iostream>

using namespace std;

int arr[1000][1000];
int BOJ5623() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	if (n == 2) {
		if (arr[0][1] == 2) {
			cout << "1 1";
			return 0;
		}
	}

	int a1 = (arr[0][1] + arr[0][2] - arr[1][2]) / 2;
	cout << a1 << ' ';
	for (int i = 1; i < n; i++) {
		cout <<(int)( arr[0][i] - a1) << ' ';
	}
	return 0;
}
