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

		int border[4] = { 0, d, n - d, n };
		sort(border, border + 4);


		if (d < n - d)
		{
			if (x >= border[0] && x <= border[1]) {
				cout << ((y >= -x + d && y <= x + d) ? "YES\n" : "NO\n");
			}
			else if (x > border[1] && x <= border[2]) {
				cout << ((y >= x - d && y <= x + d) ? "YES\n" : "NO\n");
			}
			else if (x <= border[3]) {
				cout << ((y <= -x + n + d && y >= x - d) ? "YES\n" : "NO\n");
			}

		}
		else if(n-d < d) {
			if (x >= border[0] && x <= border[1]) {
				cout << ((y >= -x + d && y <= x + d) ? "YES\n" : "NO\n");
			}
			else if (x > border[1] && x <= border[2]) {
				cout << ((y >= -x + d && y <= -x + 2*n - d) ? "YES\n" : "NO\n");
			}
			else if (x <= border[3]) {
				cout << ((y <= -x + 2*n - d && y >= x - d) ? "YES\n" : "NO\n");
			}
		}
		else {
			if (x <= d) {
				cout << ((y >= -x + d && y <= x + d) ?"YES\n" : "NO\n");
			}
			else {
				cout << ((y >= x - d && y <= -x + 3 * d) ? "YES\n" : "NO\n");
			}
		}

	}
	return 0;
}
