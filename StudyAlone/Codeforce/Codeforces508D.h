#pragma once
#include<iostream>

using namespace std;
long long temp;
int n;
long long ans;
long long ABS(long long i) {
	return i > 0 ? i : -i;
}
long long MIN(long long l1, long long l2) {
	return l1 < l2 ? l1 : l2;
}

int Codeforces508D() {
	cin >> n;
	int m = 0x7fffffff, M = -0x7fffffff;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		m = temp < m ? temp : m;
		M = temp > M ? temp : M;
		ans += ABS(temp);
	}
	if (n == 1) {
		cout << temp;
		return 0;
	}

	else {
		if (1LL * m*M > 0) {
			cout << ans - 2 * MIN(ABS(m), ABS(M));
		}
		else {
			cout << ans;
		}
	}
	return 0;
}
