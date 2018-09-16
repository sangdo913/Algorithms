#pragma once
#include<iostream>

using namespace std;
long long GCD(long long l1, long long l2) {
	long long a = l1, b = l2, r;

	if (a < b) {
		long long t = a;
		a = b;
		b = t;
	}
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
long long MIN(long long l1, long long l2){return l1 < l2 ? l1 : l2;}
int B509() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long a, b, x, y;

	cin >> a >> b >> x >> y;
	
	long long g = GCD(x, y);
	x /= g;
	y /= g;
	
	long long res = MIN(a / x, b /y);
	
	cout << res;
	
	return 0;
}
