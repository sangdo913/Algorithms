//https://www.acmicpc.net/problem/3190
// BOJ 3190 ¹ì
#pragma once
#include<iostream>
#include<deque>

using namespace std;
typedef pair<int, int> pii;
int comm[101][2];
int nd = 1;
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

deque<pii> dq;

int map[100][100], n, k;
int conv[256];

int BOJ3190() {
	cin >> n >> k;
	conv['L'] = -1;
	conv['D'] = 1;

	int r, c;
	r = c = 0;

	while (k--) {
		int ar, ac;
		cin >> ar >> ac;
		ar--; ac--;

		map[ar][ac] = 1;
	}

	int l;

	cin >> l;

	for (int i = 0; i < l; i++){
		int x;
		char t;
		cin >> x >> t;
		comm[i][0] = x;
		comm[i][1] = conv[t];
	}

	int t = 0;

	dq.push_back({ r,c });
	map[r][c] = -1;

	int tcnt = 0;

	while (true) {
		t++;
		pii next = dq.front();

		next.first += dr[nd];
		next.second += dc[nd];

		if (next.first < 0 || next.second < 0 || next.first >= n || next.second >= n) {
			break;
		}
		else if (map[next.first][next.second] == -1) break;

		else if (map[next.first][next.second] == 0) {
			pii tail = dq.back();
			map[tail.first][tail.second] = 0;
			dq.pop_back();
		}

		map[next.first][next.second] = -1;
		dq.push_front(next);

		if (comm[tcnt][0] == t) {
			nd = (4+nd + comm[tcnt++][1]) % 4;
		}
	}
	
	cout << t;

	return 0;
}
