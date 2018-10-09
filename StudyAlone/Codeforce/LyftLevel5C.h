#pragma once
#include<iostream>

using namespace std;

int memoi[100000][2];

int arr[100000];
int N;

int canwin(int a, int turn) {
	int &ret = memoi[a][turn];
	if (ret) {
		return ret;
	}

	ret = -1;

	for (int n = a - arr[a]; n >= 0; n -= arr[a]) {
		if (arr[a] > arr[n]) continue;
		if(canwin(n, turn^1) == -1)
			return ret = 1;
	}

	for (int n = a + arr[a]; n <= N; n += arr[a]) {
		if (arr[a] > arr[n]) continue;
		if (canwin(n, turn ^ 1) == -1)
			return ret = 1;
	}

	return ret;
}

int LyftLevel5C() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < N; i++) {
		if (canwin(i, 0) == 1) {
			cout << 'A';
		}
		else {
			cout << 'B';
		}
	}
	return 0;
}