//https://www.acmicpc.net/problem/4811
//BOJ4811 ¾Ë¾à

#pragma once
#include<iostream>
#include<cstring>

using namespace std;

long long cache[31][31];

long long getPill(int w, int h) {
	if (h == 1 && w == 0) {
		return cache[w][h] = 1;
	}

	long long& num = cache[w][h];
	if (num != 0) return num;

	if (w >= 1) {
		num += getPill(w - 1, h+1);
	}
	if (h >= 1) {
		num += getPill(w, h - 1);
	}
	return num;
}

int BOJ4811() {
	int w;
	
	while (cin >> w) {
		if (w == 0) break;

		memset(cache, 0, sizeof(cache));

		cout << getPill(w, 0) << '\n';
	}
	return 0;
}
