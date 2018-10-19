//https://www.acmicpc.net/problem/12872
//BOJ 12872 플레이리스트
#pragma once
#include<iostream>
#include<cstring>

const int MOD = 1000000007;
using namespace std;

int dp[101][101][101];
int n,m,k;

int  getall(int len, int block,int diff) {
	if (len == k) {
		if (diff == n) return 1;
		return 0;
	}

	if (n-block == 0) return 0;

	int& res = dp[len][block][diff];
	if (res != -1) return res;
	res = 0;

	if (block == m) {
		if(diff < n) res += (1LL *(n-diff)*getall(len + 1, block, diff+1 ))%MOD;
		res += (1LL*(diff-block)*getall(len + 1, block, diff)) % MOD;
	}
	else {
		if (diff < n) res += (1LL * (n - diff)*getall(len + 1, block + 1, diff + 1)) % MOD;
	}

	return res;
}


int BOJ12872() {
	cin >> n >> m >> k;
	
	memset(dp, -1, sizeof(dp));

	cout << getall(0, 0,0);

	return 0;
}
