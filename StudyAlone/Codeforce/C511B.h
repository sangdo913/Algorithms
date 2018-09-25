#pragma once
#include<iostream>

using namespace std;

int C511B() {
	int n;
	cin >> n;
	int res = 0;

	while (n--) {
		int a, b;
		cin >> a >> b;
		int sum = a + b;
		res = sum > res ? sum : res;

	}

	cout << res;
	return 0;
}