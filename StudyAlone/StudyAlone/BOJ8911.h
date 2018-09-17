//https://www.acmicpc.net/problem/8911
//∞≈∫œ¿Ã
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

char comm[501];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int BOJ8911() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	while (n--) {
		int nd = 0;

		cin >> comm;
		int len = strlen(comm);

		int x[2] = { 0, 0 };
		int y[2] = { 0, 0 };
		int pos[2] = { 0,0 };
		for (int c = 0; c < len; c++) {
			switch(comm[c]) {
			case 'F':
				pos[0] += dr[nd];
				pos[1] += dc[nd];
				break;
			case 'B':
				pos[0] -= dr[nd];
				pos[1] -= dc[nd];
				break;
			case'R':
				nd++;
				nd %= 4;
				break;
			case'L':
				nd += 4;
				nd--;
				nd %= 4;
			}

			x[1] = x[1] < pos[1] ? pos[1] : x[1];
			x[0] = x[0] > pos[1] ? pos[1] : x[0];
			y[1] = y[1] < pos[0] ? pos[0] : y[1];
			y[0] = y[0] > pos[0] ? pos[0] : y[0];
		}

		cout << (x[1] - x[0]) * (y[1] - y[0]) << '\n';
	}
	return 0;
}
