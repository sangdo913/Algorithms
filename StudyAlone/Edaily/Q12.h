#pragma once
#include<iostream>

#include<vector>
using namespace std;

int Q12() {
	int n;
	vector<int> vec;

	cin >> n;

	for (int i = n; i < n + n; i++) {
		vec.push_back(i);
	}

	cout << '{';
	cout << vec[0];
	for (int i = 1; i < vec.size(); i++) {
		cout << ',' << vec[i];
	}
	cout << '}';
	return 0;
}
