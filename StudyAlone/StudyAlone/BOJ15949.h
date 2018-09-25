//https://www.acmicpc.net/problem/15949
//piet
#pragma once
#include<iostream>
#include<vector>
#include<cstring>

#include<queue>
#include<stack>

using namespace std;

int n, m;
char pixel[102][102];

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0,1,0,-1 };

int ndp = 1, cc = -1;

pair<int, int> pos;

pair<int, int> move() {
	
	queue<pair<int, int> > que;
	stack<pair<int, int> > st;

	bool visit[102][102] = {};
	visit[pos.first][pos.second] = true;

	que.push(pos);

	char bl = pixel[pos.first][pos.second];
	while (que.size()) {
		pair<int, int> now = que.front();
		st.push(now);
		que.pop();

		for (int d = 0; d < 4; d++) {
			pair<int, int> next = { now.first + dr[d], now.second + dc[d] };
			if (visit[next.first][next.second]) continue;
			if (bl != pixel[next.first][next.second]) continue;
			
			visit[next.first][next.second] = true;
			que.push(next);
		}
	}

	pair<int, int> res;
	vector<pair<int, int> > container[4];
	int x[2] = {0x7fffffff, -0x7fffffff}, y[2] = {0x7fffffff, -0x7fffffff};
	
	while (st.size()) {
		pair<int, int > now = st.top();
		st.pop();

		if (x[0] > now.second) {
			x[0] = now.second;
			container[3].clear();
			container[3].push_back(now);
		}
		else if (x[0] == now.second) {
			container[3].push_back(now);
		}
		if (x[1] < now.second) {
			x[1] = now.second;
			container[1].clear();
			container[1].push_back(now);
		}

		else if (x[1] == now.second) {
			container[1].push_back(now);
		}

		if (y[0] > now.first) {
			y[0] = now.first;
			container[0].clear();
			container[0].push_back(now);
		}
		else if (y[0] == now.first) {
			container[0].push_back(now);
		}

		if (y[1] < now.first) {
			y[1] = now.first;
			container[2].clear();
			container[2].push_back(now);
		}
		else if (y[1] == now.first) {
			container[2].push_back(now);
		}
	}
		
	int ccc = (ndp + 4 + cc) % 4;

	res = container[ndp][0];

	for (int i = 1; i < container[ndp].size(); i++) {
		pair<int, int> &now = container[ndp][i];

		switch (ccc) {
		case 0:
			if (now.first < res.first) {
				res = now;
			}
			break;
		case 1:
			if (now.second > res.second) {
				res = now;
			}
			break;

		case 2:
			if (now.first > res.first) {
				res = now;
			}
			break;
		case 3:
			if (now.second < res.second) {
				res = now;
			}
			break;
		}
	}
	
	res.first += dr[ndp];
	res.second += dc[ndp];
	return res;
}

int BOJ15949() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	memset(pixel, 'X', sizeof(pixel));

	for (int i = 1; i <= n; i++) {
		cin >> pixel[i] + 1;
		pixel[i][m + 1] = 'X';
	}

	
	pos.first = 1; pos.second = 1;
	cout << pixel[1][1];

	while (true) {
		bool find = false;
		for (int i = 0; !find && i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				pair<int, int> next = move();
				if (pixel[next.first][next.second] != 'X') {
					cout << pixel[next.first][next.second];
					find = true;
					pos = next;
					break;
				}
				if (!find) {
					cc = -cc;
				}
			}
			if (!find) {
				ndp++;
				ndp %= 4;
				cc = -cc;
			}
		}
		if (!find) break;
	}
	
	return 0;
}