#pragma once
#include<iostream>
#include<cstring>
using namespace std;

int cache[200][10000];

char str[101];
int l;
bool canfind(int idx, int flag) {
	int& ret = cache[idx][flag];

	if (ret != -1) return ret;

	if (idx == l) {
		return true;
	}

	int cnt = 0;

	ret = 0;

	for (int i = idx; i < l; i++) {
		cnt += str[i] - '0';
		if (cnt == flag) {
			ret |= canfind(i + 1, flag);
		}
	}

	return ret;
}

int C512C() {
	cin >> l >> str;
	memset(cache, -1, sizeof(cache));

	int cnt = 0;
	for (int i = 0; i < l - 1; i++) {
		cnt += str[i] - '0';
		bool res = canfind(i + 1, cnt);
		if (res) {
			cout << "YES\n";
			return 0;
		}
	}
	
	cout << "NO\n";
	return 0;
}