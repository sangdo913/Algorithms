//POLE
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int n, l, r;
long long f[21];
long long comb[21][21];
long long memoi[21][21];

long long cal(int n, int bn) {
	if (bn == 1) {
		return f[n - 1];
	}

	long long &ret = memoi[n][bn];
	
	if(ret != -1) return memoi[n][bn];

	ret = 0;

	for (int i = 0; i <= n - bn; i++) {
		ret += (comb[n-1][i] * f[i])*cal(n - 1 - i, bn - 1);
	}
	return ret;
}

int SWEA3993() {
	f[0] = 1;
	comb[0][0] = 1;

	memset(memoi, -1, sizeof(memoi));
	
	for (int i = 1; i <= 20; i++) {
		f[i] = f[i - 1] * i;
		comb[i][0] = 1;
		comb[i][i] = 1;

		for (int j = 1; j < i; j++) {
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
	}

	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {

		cin >> n >> l >> r;

		if (l == 1 && r == 1) {
			cout << '#' << tc << ' '<< (n == 1 ? 1 : 0) <<  '\n';
			continue;
		}

		long long res = 0;
		if (l == 1) {
			res = cal(n - 1, r-1);
		}
		else if (r == 1) {
			res = cal(n - 1, l - 1);
		}
		else {
			int s = l - 1, e = n - r;
			for (; s <= e; s++) {
				res += comb[n-1][s]*cal(s, l - 1)*cal(n - s - 1, r - 1);
			}
		}
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}