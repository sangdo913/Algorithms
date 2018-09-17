#pragma once
#include<iostream>

using namespace std;
int dr[4] = { 0,0, -1,-1 };
int dc[4] = { 0,-1,0,-1 };
long long max(long long l1, long long l2) { return l1 < l2 ? l2 : l1; }
long long min(long long l1, long long l2) { return l1 < l2 ? l1 : l2; }
int EduCodeforce50B() {
	int t;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> t;

	while (t--) {
		long long x, y, k;
		cin >> x >> y >> k;

		long long r[4], c[4];

		for (int i = 0; i < 4; i++) {
			r[i] = y + dr[i];
			c[i] = x + dc[i];
		}
		long long res;
		if ((r[0] + c[0]) % 2 == 0) {
			long long cnt = max(r[0], c[0]);
			long long res = 0x7fffffffffffffff;
			if (k - cnt >= 0 && (k-cnt)%2 == 0) {
				res = min(k, res);
				cout << res << '\n'; continue;
			}
			cnt = max(r[3], c[3]);
			if (k - cnt >= 2 && (k - cnt) % 2 == 0) {
				res = min(k-2, res);
				cout << res << '\n'; continue;
			}



			else {
				cout << -1 << '\n'; continue;
			}
		}
		else {
			if (max(r[1], c[1]) >= k && max(r[2], c[2]) >= k) {
				cout << -1 << '\n'; continue;
			}
			cout << k - 1 << '\n'; continue;
		}
	}
	return 0;
}