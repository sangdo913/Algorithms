#pragma once
#include<iostream>
using namespace std;
long long GCD(long long a, long long b) {
	long long r;
	if (a < b) {
		long long temp = a;
		a = b;
		b = a;
	}
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int C512D() {
	long long n, m, k;
	
	cin >> n >> m >> k;

	if ((n*m * 2) % k != 0) {
		cout << "NO\n"; return 0;
	}

	long long gx = GCD(2 *n, k);
	long long gy = GCD(2* m, k);
	
	cout << "YES\n";

	if (gy != 1) {
		cout << "0 0\n";
		cout << 0 << ' ' << 2* m / gy << '\n';
		cout << n / (k / gy) << ' ' << 0 << '\n';
	}
	else {
		cout << "0 0\n";
		cout << 0 << ' ' << m / (k / gy) << '\n';
		cout << 2 * n / gx << ' ' << 0 <<'\n';
	}

	return 0;
}
