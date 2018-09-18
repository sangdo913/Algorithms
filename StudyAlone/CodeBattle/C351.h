#pragma once
#include<iostream>
using namespace std;


long long pow(int cnt, int num) {
	if (cnt == 0) return 1;

	long long half = pow(cnt / 2, num);
	half *= half;
	return cnt & 1 ? half * num : half;
}

int C351() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		long long x;
		cin >> x;

		bool ok = false;
		long long n = 1;
		for (; n*n*n <= x; n++) {
			if (n*n*n == x) {
				cout << '#' << t << ' ' << n << '\n';
				ok = true;
				break;
			}
		}
		
		if (ok) continue;
		cout << '#' << t << ' ' << -1 << '\n';
	}
	return 0;
}
