//https://www.acmicpc.net/problem/1629
//BOJ 1629
#pragma once
#include<iostream>

using namespace std;

long long r;
int MUL(int x, int cnt) {
	if (cnt == 0) return 1;

	long long half = MUL(x, cnt / 2);
	half *= half;
	half %= r;

	return cnt & 1 ? (half*x) % r : (half)%r;
}

int BOJ1629() {
	int a, b;
	cin >> a >> b >> r;

	cout << MUL(a, b);
	return 0;
}
