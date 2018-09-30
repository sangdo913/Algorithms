#pragma once
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>

using namespace std;

enum dir{ UP = 0b0001, DOWN = 0b0010, LEFT = 0b0100, RIGHT = 0b1000 };
int conv[9];
int map[52][52];
char contry[52][52];

int info[52][52];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int cant[9];

queue<pair<int, int> > que[256];
bool cantake(int r, int c) {
	int e[256] = {};
	char cs[4] = {};
	int ns[4] = {};


	for (int d = 0; d < 4; d++) {
		e[contry[r + dr[d]][c + dc[d]]]++;
	}
	bool allsame = true;
	int nums = 0;
	for (int i = 'A'; i <= 'Z'; i++) {
		if (e[i] != 0) {
			if (nums != 0) nums = e[i];
			else {
				if (e[i]);
			}
		}
	}
}
bool checkNum(int r, int c,char con) {
	int mnum = 0;
	int nnum = 0;

	int cmp = info[r][c];
	for (int i = 0; i < 4; i++) {
		char C = contry[r + dr[i]][c + dc[i]];
		if (C == cmp) {
			mnum++;
		}
		else if (C == con) {
			nnum++; continue;
		}
	}
	return nnum > mnum;
}

int cons[100];
int ccnt = 0;

int nhn4() {
	cant[UP] = DOWN;
	cant[DOWN] = UP;
	cant[LEFT] = RIGHT;
	cant[RIGHT] = LEFT;

	int n;
	cin >> n;
	int cnt = 1;

	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n + 1; j++) {
			map[i][j] = 0b1111;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			char in;
			cin >> in;
			if (in >= 'A' && in <= 'Z') {
				contry[i][j] = in;
				cons[ccnt++] = in;

				que[in].push({ i,j });
			}
			else {
				map[i][j] = in - '0';
			}
		}
	}

	bool changed = true;

	while (changed) {
		for (int i = 0; i < ccnt; i++) {
			int qcnt = que->size();
			while (qcnt--) {
				pair<int, int> now = que[cons[i]].front();

				for (int d = 0; d < 4; d++) {
					pair<int, int> next;
					next.first += now.first + dr[d];
					next.second += now.second + dc[d];

					if (cant[d] == map[next.first][next.second]) continue;
					
					if (info[next.first][next.second] == 0) {
						info[next.first][next.second] = cons[i];
					}
					else if (info[next.first][next.second] && checkNum(next.first,next.second, cons[i])) {
						info[next.first][next.second] = cons[i];
					}

				}
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {

			}
		}
	}

	
	return 0;
}