//https://www.acmicpc.net/problem/1767
//BOJ 1767 N-Rook ll
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000001;
int cache[101][101][101];

int result(int r, int c, int cnt) {
	if (cnt == 0) { return 1; }
	
	int &res = cache[r][c][cnt];
	if (res != -1) return res;
	res = 0;

	if (c >= 2 && r >= 1 && cnt >= 2) {
		res += (1LL*c*(c-1)/2*result(r-1, c-2,cnt-2))%MOD;
		res %= MOD;
	}
	if (r >= 2 && c >= 1 && cnt >=2) {
		res += (1LL * c*(r - 1)*result(r - 2, c - 1, cnt - 2)) % MOD;
		res %= MOD;
	}

	if (c >= 1 && r >= 1) {
		res += (1LL * c*result(r - 1, c-1, cnt - 1)) % MOD;
		res %= MOD;
		res += result(r - 1, c, cnt) % MOD;
		res %= MOD;
	}
	
	return res;
}

int BOJ1767() {
	memset(cache, -1, sizeof(cache));
	int r, c, cnt;
	cin >> r >> c >> cnt;

	cout << result(r, c, cnt);
	
	return 0;
}