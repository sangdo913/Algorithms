//https://www.acmicpc.net/problem/2292
//¹úÁý
#pragma once
#include<iostream>

using namespace std;

int BOJ2292() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	
	cin >> n;

	int cnt = 1;
	int i = 0;

	while (cnt < n) {
		i ++;
		cnt += i*6;
	}

	cout << ++i << '\n';
	return 0;
}
