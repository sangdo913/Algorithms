//https://www.acmicpc.net/problem/15661
//BOJ 15661 링크와 스타트
#pragma once
#include<iostream>
using namespace std;

int n;
int arr[20][20];
int abs(int i) { return i > 0 ? i : -i; }

int getZeros(int bit) {
	int res = 0;
	while ((bit & 1) == 0) res++, bit>>=1;

	return res;
}
int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int func(int bit) {
	int res[2] = { 0 };

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			int b1 = 1 << i, b2 = 1 << j;

			if (bool(bit & b1) == bool(bit&b2)) {
				res[bool(bit&b1)] += arr[i][j] + arr[j][i];
			}
		}
	}

	return abs(res[0] - res[1]);
}

int BOJ15661() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> arr[i][j];
	}

	int res = 0x3f3f3f3f;
	int bit = (1 << (n/2)) -1;
	while (bit < 1 << n) {
		int temp = bit | ((bit&-bit)-1);

		res = MIN(res, func(bit));

		int nextbit = (temp + 1) | (((~temp & -~temp)-1) >> (getZeros(bit) + 1));
		bit = nextbit;
	}
	cout << res;
	return 0;
}
