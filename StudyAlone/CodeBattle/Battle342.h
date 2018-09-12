#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int qlen[500];
char comp[6] = "croak";
char q[2501];
int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }
int Battle342() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> q;

		memset(qlen, 0, sizeof(qlen));
		int len = strlen(q);
		int cnt = 0;
		bool find = true;

		for (int i = 0; i < len; i++) {
			find = false;
			for (int j = 0; j < 500; j++) {
				if (comp[qlen[j]] == q[i]) {
					cnt = MAX(cnt, j + 1);
					qlen[j] ++;
					if (qlen[j] == 5) {
						qlen[j] = 0;
					}
					find = true;
					break;
				}
			}
			if (find == false) {
				cnt = -1;
				break;
			}

		}
		for (int i = 0; i < 500; i++) {
			if (qlen[i]) {
				cnt = -1;
				break;
			}
		}
		if (cnt) cout << '#' << tc << ' ' << cnt << '\n';
	}
	return 0;
}
