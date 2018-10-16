//https://www.acmicpc.net/problem/12906
//BOJ 12906 새로운 하노이 탑
#pragma once
#include<iostream>
#include<string>
#include<tuple>
#include<unordered_set>
#include<set>
#include<queue>

using namespace std;
typedef tuple<string, string, string> sss;
string stick[3];
set<tuple<string, string, string> > se;
queue<sss> que;

bool check(sss& s) {
	stick[0] = get<0>(s);
	stick[1] = get<1>(s);
	stick[2] = get<2>(s);

	for (int i = 0; i < stick[0].size(); i++) if (stick[0][i] != 'A') return false;
	for (int i = 0; i < stick[1].size(); i++) if (stick[1][i] != 'B') return false;
	for (int i = 0; i < stick[2].size(); i++) if (stick[2][i] != 'C') return false;
	return true;
}

sss fromto(sss &s, int f, int t) {
	string next[3];
	tie(next[0], next[1], next[2]) = s;

	if (next[f].size() == 0) return {"D", "",""};

	next[t].push_back(next[f].back());
	next[f].pop_back();
	return make_tuple(next[0], next[1], next[2]);
;
}

void push(sss &s) {
	if (se.find(s) == se.end()) {
		se.insert(s);
		que.push(s);
	}
}
int bfs() {
	que.push({ stick[0],stick[1], stick[2] });
	se.insert({ stick[0],stick[1], stick[2] });
	int ti = 0;

	while (que.size()) {
		int cnt = que.size();
		while (cnt--) {
			sss now = que.front(); que.pop();
			if (check(now)) return ti;

			sss next = fromto(now, 0, 1);
			push(next);

			next = fromto(now, 0, 2);
			push(next);

			next = fromto(now, 1, 0);
			push(next);

			next = fromto(now, 1, 2);
			push(next);
			
			next = fromto(now, 2, 0);
			push(next);

			next = fromto(now, 2, 1);
			push(next);
		}
		ti++;
	}
	return -1;
}


int BOJ12906() {
	int n;
	for (int i = 0; i < 3; i++) {
		cin >> n;
		if (n) cin >> stick[i];
	}
	cout << bfs();
	return 0;
}
