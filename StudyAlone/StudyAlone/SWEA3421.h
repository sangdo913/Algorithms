#include<iostream>#pragma once
#include<cstring>
using namespace std;

int not[21];
int n, m;

bool canmake(int bit) {

	for (int i = 1; i <= n; i++) {
		if ((bit & (1 << i)) == 0) continue;
		int check = bit & not[i];
		if (check) return false;
	}
	return true;
}

int SWEA3421() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		memset(not, 0, sizeof(not));
		int a, b;

		cin >> n >> m;

		while (m--) {
			cin >> a >> b;

			not[a] |= 1 << b;
		}

		int res = 0;
		for (int i = 0; i < (1 << n); i++) {
			res += canmake(i<<1);
		}

		cout << '#' << ' ' << tc << ' ' << res << '\n';
	}
	return 0;
}
