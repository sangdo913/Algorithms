#pragma once
#include<iostream>
using namespace std;

int C512D() {
	long long n, m, k;
	
	cin >> n >> m >> k;

	if ((n*m * 2) % k != 0) {
		cout << "NO\n"; return 0;
	}

	for (long long i = 1; i*i <= n * m * 2 / k; i++) {
		if ((n*m*2 / k) % i == 0) {
			long long j = n * m*2 / k / i;
			if (j <= m) {
				cout << "YES\n"; 
				cout << 0 << ' ' << 0 << '\n';
				cout << i << ' ' << 0 << '\n';
				cout << 0 << ' ' << j << '\n';
				return 0;
			}

			else if (j <= n) {
				cout << "YES\n";
				cout << 0 << ' ' << 0 << '\n';
				cout << j << ' ' << 0 << '\n';
				cout << 0 << ' ' << i << '\n';
				return 0;
			}
		}
	}
	
	return 0;
}
