//https://www.acmicpc.net/problem/12996
//BOJ12996 Acka
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000007;

int cache[51][51][51][51];

int sing(int len, int a, int b, int c) {
	if (len == 0) {
		if (a == 0 && b == 0 && c == 0) { return 1; }
		else { return 0; }
	}

	int &res = cache[len][a][b][c];
	if (res!=-1) return res;
	res = 0;

	len--;
	int temp[7] = {};
	if (a > 0) temp[0] = sing(len, a - 1, b, c) ;
	if (b > 0)  temp[1] = sing(len, a, b - 1, c);
	if (c > 0) temp[2] = sing(len, a, b , c-1);
	if (a > 0 && b > 0) temp[3] = sing(len, a - 1, b - 1, c);
	if (a > 0 && c > 0) temp[4] = sing(len, a - 1, b, c - 1);
	if (b > 0 && c > 0) temp[5] = sing(len, a, b - 1, c - 1);
	if (a > 0 && b > 0 && c > 0) temp[6] = sing(len, a - 1, b - 1, c - 1);
	for (int i = 0; i < 7; i++) res += temp[i] > 0 ? temp[i] : 0, res %= MOD;

	return res;
}
int BOJ12996() {
	memset(cache, -1, sizeof(cache));
	int s, a, b, c;

	cin >> s >> a >> b >> c;

	cout << sing(s, a, b, c);
	return 0;
}
