//https://www.acmicpc.net/problem/10989
//BOJ 10989  수 정렬하기3
#pragma once
#include<iostream>

using namespace std;

int nums[10001];

int BOJ10989() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		nums[num]++;
	}

	for (int i = 1; i <= 10000; i++) {
		while (nums[i]) {
			cout << i << '\n';
			nums[i]--;
		}
	}
	return 0;
}
