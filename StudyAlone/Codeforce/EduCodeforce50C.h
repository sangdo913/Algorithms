#pragma once
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

int nums[19];

long long canNum[1000000];
int nNum;
int dNum;

vector<long long> se;

long long getNum() {
	long long ret = 0;
	for (int i = 0; i < 18; i++) {
		ret *= 10;
		ret += nums[i];
	}
	return ret;
}
void makeNum(int depth, int lenth) {
	if (depth == dNum) {
		se.push_back(getNum());
		return;
	}
	if (lenth == 18) return;

	makeNum(depth, lenth + 1);
	
	for (int i = 1; i < 10; i++) {
		nums[lenth] = i;
		makeNum(depth + 1, lenth + 1);
		nums[lenth] = 0;
	}

	return;
}
int EduCodeforce50C() {
	for (int i = 1; i < 4; i++) {
		dNum = i;
		makeNum(0, 0);
	}
	se.push_back(0);
	se.push_back(1e18);
	sort(se.begin(), se.end());

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	while (t--) {
		long long a, b;
		cin >> a >> b;

		auto st = lower_bound(se.begin(), se.end(), a);
		auto ed = upper_bound(se.begin(), se.end(), b);
		int cnt = (ed - st);
		cout << cnt << '\n';

	}
	return 0;
}