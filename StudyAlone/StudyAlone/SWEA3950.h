//SWEA 3950
// °ýÈ£
#pragma once
#include<iostream>

using namespace std;

char str[1001];
int st[1001];
int ridx[1001];

int SWEA3950() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int l;
		cin >> l;
		cin >> str;

		int ocnt = 0;
		int top = 0;
		int cidx[2] = { -1,-1 };

		for (int i = 0; i < l; i++) {
			if (str[i] == '(') {
				st[ocnt++] = i;
			}
			
			else {
				if (ocnt) ocnt--;
				else {
					ridx[top++] = i;
					if (cidx[0] == -1) cidx[0]  = i;
					cidx[1] = i;
				}
			}
		}

		int res = 0;
		int progress[2][2];
		
		if (top) {
			if (ocnt) {
				progress[res][0] = cidx[0];
				progress[res][1] = cidx[1];
				res++;
			}
			else {
				progress[res][0] = cidx[0];
				progress[res][1] = ridx[(top - 1) / 2];
				res++;
			}
		}

		for (int i = 0; i < ocnt; i++) ridx[top++] = st[i];

		if (ocnt) {
			progress[res][0] = ridx[(top-1) / 2 + 1];
			progress[res][1] = ridx[top - 1];
			res++;
		}
		
		if (l & 1) {
			cout << '#' << tc << ' ' << -1 << '\n';
		}

		else {
			cout << '#' << tc << ' ' << res << '\n';
			for (int i = 0; i < res; i++) {
				cout << progress[i][0] << ' ' << progress[i][1] << '\n';
			}
		}
		
	}
	return 0;
}
