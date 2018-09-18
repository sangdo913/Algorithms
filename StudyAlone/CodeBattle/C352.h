#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int cache[300001];
char nums[300001];
int n, m;
const int MOD = 1000000007;

int  pow(int cnt) {
	if (cnt == 0) return 1;
	long long half = pow(cnt / 2);
	half *= half;
	half %= MOD;
	return cnt & 1 ? (half * 2)%MOD :half;
}
int getNum() {
	int cnt = 0;
	int num = 0;
	for (int i = 0; i < n; i++) {
		num *= 10;
		num += nums[i] - '0';
		num %= m;
		if (num  == 0) {
			cnt++;
		}
	}
	if (num) return 0;

	return pow(cnt-1);
}
int C352() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		cin >> nums;
		cout << '#' << tc << ' ' << getNum() <<'\n';
	}

	return 0;
}

