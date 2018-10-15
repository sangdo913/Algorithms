//https://www.acmicpc.net/problem/2916
//BOJ 2916 자와 각도기
#pragma once
#include<iostream>

using namespace std;

bool check[1000];
int que[1000], f, r;

int abs(int i) { return i > 0 ? i : -i;}

int BOJ2916() {
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		int can;
		cin >> can;
		check[can] = true;
		que[r++] = can;
	}

	while (f != r) {
		int now = que[f++];
		for (int i = 0; i <= 360; i++) {
			if (check[i]) {
				int deg;
				if (!check[(now + i) % 360]) {
					check[(now + i) % 360] = true;
					que[r++] = (now + i) % 360;
				}
				deg = (now + i) % 360;
				deg = 360 - deg;
				if (!check[deg]) {
					check[deg] = true;
					que[r++] = deg;
				}
				deg = abs(now - i);
				if (!check[deg]) {
					check[deg] = true;
					que[r++] = deg;
				}
				deg = 360 - deg;
				if (!check[deg]) {
					check[deg] = true;
					que[r++] = deg;
				}
			}
		}
	}

	while (k--) {
		int deg;
		cin >> deg;
		cout << (check[deg] ? "YES\n" : "NO\n");
	}
	return 0;
}
