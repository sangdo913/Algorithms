//https://www.acmicpc.net/problem/12970
//BOJ 12970 AB
#pragma once
#include<iostream>
#include<string>

using namespace std;

int cache[51][25*49+1][25*49+1];
string s;
int n, k;

int get(int len,int a, int cnt) {
	if (len == n) {
		if (cnt == k) return 1;
		else return -1;
	}

	if (cnt > k) return -1;

	int& res = cache[len][a][cnt];
	if (res) return res;

	len++;
	s.push_back('A');
	res = get(len, a + 1, cnt);
	if (res == 1) return 1;
	s.pop_back();

	s.push_back('B');
	res = get(len, a, cnt + a);
	if (res == 1) return 1;
	s.pop_back();

	return res;
}

int BOJ12970() {
	cin >> n >> k;

	if (get(0, 0, 0) ==-1) cout << -1;
	else cout << s;
	return 0;
}
