//https://www.acmicpc.net/problem/5528
//OIO ¿­Â÷
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

char train[2][2001];
int cache[2001][2001][2];
int conv[2] = { 'O', 'I' };

int n, m;

int MAX(int i1, int i2) { return i1 < i2 ? i2 : i1; }

int trainLen(int flag, int s, int t) {
	int &ret = cache[s][t][flag];
	if (ret != -1) return ret;

	if (s >= n && t >= m) return 0;

	int ns = s;
	int nt = t;

	int ts, tt;
	if (s < n && t < m && conv[flag] == train[0][s] && conv[flag] == train[1][t]) {
		ts = ns >= n ? 0 : trainLen(flag ^ 1, s + 1, t);
		tt = nt >= m ? 0 : trainLen(flag ^ 1, s, t + 1);
		ret = MAX(ts, tt);
	}

	else if (s < n && conv[flag] == train[0][s]) {
		ret = trainLen(flag ^ 1, s + 1, t);
	}
	else if (t < m && conv[flag] == train[1][t]) {
		ret = trainLen(flag ^ 1, s, t + 1); 
	}

	else {
		return 0;
	}

	if (flag == 1 && ret == 1) ret = 0;
	if (flag == 0 && ret == 0) ret = -1;
	return ++ret;
}


int BOJ5528() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n >> m;

	cin >> train[0];
	cin >> train[1];


	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res = MAX(res, trainLen(1, i, j));
		}
	}

	cout << res;
	return 0;
}
