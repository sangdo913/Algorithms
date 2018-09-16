#pragma once
#include<iostream>

using namespace std;

int A509() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int min = 0x7fffffff;
	int max = 0;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		max = max < num ? num : max;
		min = num < min ? num : min;
	
	}
	cout << max - min + 1 - n;
	return 0;
}