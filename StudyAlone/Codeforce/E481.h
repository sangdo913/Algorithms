//Codeforces 481 E Bus Video System
#pragma once
#include<iostream>

using namespace std;

int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }
int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int E481() {
	int n, w;
	cin >> n >> w;

	int mmin = 0x7fffffff, mmax = 0xffffffff;
	int now = 0;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		now += num;
		mmin = MIN(mmin, now);
		mmax = MAX(mmax, now);
	}

	mmin = mmin < 0 ? -mmin : 0;
	mmax = mmax < 0 ? 0 : mmax;
	if (mmin > w || mmax > w) { cout << 0 << endl; return 0; }
	mmax = w-mmax > 0 ? w-mmax : 0;
	
	int res = mmax - mmin + 1;
	cout << (res < 0 ? 0 : res);
	return 0;
}
