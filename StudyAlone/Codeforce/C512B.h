#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

int n, d, m;

int C512B() {
	int n, d;
	cin >> n >> d;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		if (y <= x + d && y <= -x + 2 * n - d && y >= -x + d && y >= x - d) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}

	}
	return 0;
}
