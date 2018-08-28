#pragma once
#include<iostream>
#include<cstring>
using namespace std;

char info[100001];

int C322() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	for (register int tc = 1; tc <= t; tc++) {
		cin >> info;
		int land = 1;

		int len = strlen(info);
		int res = 0;
		char pr = info[0];
		for (register int i = 1; i < len; i++) {
			if (info[i] == ')') {
				land--;
				if (info[i - 1] == '(') {
					res += land;
				}
				else {
					res++;
				}
			}
			else {
				land++;
			}
		}
		cout << '#' << tc << ' ' << res << '\n';
	}
	return 0;
}