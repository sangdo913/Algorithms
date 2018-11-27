//https://www.acmicpc.net/problem/4902
//ทฮวม

#pragma once
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

long long MAX(long long l1, long long l2) { return l1 < l2 ? l2 : l1; }

int BOJ2217() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<int> vec;

	int n;
	cin >> n;

	while (n--) {
		long long in;

		cin >> in;

		vec.push_back(in);
	}

	sort(vec.begin(), vec.end());

	long long res = 0;
	for (int i = 0; i < vec.size(); i++) {
		res = MAX(res, 1LL*vec[i] * (vec.size() - i));
	}
	cout << res;
	return 0;
}

