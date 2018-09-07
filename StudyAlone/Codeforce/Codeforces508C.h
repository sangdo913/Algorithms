#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

int arr[2][1000000];

int Codeforces508C() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[0][i];
	}
	for (int i = 0; i < n; i++) {
		cin >> arr[1][i];
	}

	sort(arr[0], arr[0] + n);
	sort(arr[1], arr[1] + n);

	int len[2] = { n-1,n-1};
	int turn = 0;
	long long score[2] = {};
	for (int i = 0; i < 2 * n; i++) {
		if (len[turn] == -1) {
			len[turn ^ 1]--;
			turn ^= 1;
			continue;
		}

		if (len[turn ^ 1] == -1) {
			score[turn] += arr[turn][len[turn]--];
			turn ^= 1;
			continue;
		}

		if (arr[turn][len[turn]] < arr[turn^1][len[turn ^ 1]]) {
			len[turn ^ 1]--;
		}
		else {
			score[turn] += arr[turn][len[turn]--];
		}
		turn ^= 1;
	}
	cout << score[0] - score[1];
	return 0;
}
