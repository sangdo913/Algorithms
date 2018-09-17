//https://www.acmicpc.net/problem/5525
//IOIOI

#pragma once
#include<iostream>

int kmp[1000000];
char ioi[2000002];
char str[1000001];
using namespace std;
int n, m;

void make() {
	int len = 2 * n + 1;
	for (int i = 0; i < len; i++) {
		ioi[i] = i & 1 ? 'O' : 'I';
	}

	int i = 0, j = 0;
	kmp[0] = -1;
	for (int i = 1; i < len; i++) {
		kmp[i] = j;
		while (j != -1 && ioi[j] != ioi[i]) j = kmp[j];
		j++;
	}

}
int BOJ5525() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >>  str;
	make();

	int j = 0;
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		while (j != -1 && ioi[j] != str[i]) {
			j = kmp[j];
		}

		j++;
		
		if (j == 2 * n + 1) {
			cnt++;
			j -= 2;
		}
	}
	cout << cnt << '\n';

	return 0;
}