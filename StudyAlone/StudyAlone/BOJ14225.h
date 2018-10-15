//https://www.acmicpc.net/problem/14225
//BOJ 14225 부분 수열의 합
#pragma once
#include<iostream>

int arr[20];
bool nums[2000001];
using namespace std;

int BOJ14225() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) cin >> arr[i];

	for (int i = 1; i < 1 << n; i++) {
		int bit = i, idx = 0;
		int num = 0;

		while (bit) {
			if (bit & 1) {
				num += arr[idx];
			}
			idx++; bit >>= 1;
		}

		nums[num] = true;
	}

	for (int i = 1; i <= 2000000; i++) {
		if (nums[i] == false) { cout << i; break; }
	}
	return 0;
}
