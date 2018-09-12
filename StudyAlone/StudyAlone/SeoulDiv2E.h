#pragma once
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
using namespace std;

int conv[256];
int info[8][3];
deque<int> de;

int SeoulDiv2E() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	conv['W'] = 0;
	conv['B'] = 1;
	conv['O'] = 2;
	conv['G'] = 3;
	conv['R'] = 4;
	conv['Y'] = 5;

	for (int i = 0; i < 8; i++) {
		char in[3];
		cin >> in[0] >> in[1] >> in[2];

		info[i][0] = conv[in[0]];
		info[i][1] = conv[in[1]];
		info[i][2] = conv[in[2]];

		for (int i = 0; i < 3; i++) {
			int a[3] = { info[i][(0 + i) % 3], info[i][(1 + i) % 3], info[i][(2 + i) % 3] };
			if (len[a[0]] == 0) {

			}
		}
	}
	
	bool r = res(0);
	cout << (r ? "YES" : "NO");

	return 0;
}
