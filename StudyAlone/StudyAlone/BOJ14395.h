//https://www.acmicpc.net/problem/14395
//BOJ 3568 4¿¬»ê
#pragma once
#include<iostream>
#include<set>
#include<string>
#include<queue>
#include<tuple>
#include<map>

using namespace std;

typedef pair<long long, string> psi;
map<long long, string> mp;
queue<psi> que;
char oper[4] = { '*', '+', '-', '/' };
const long long INF = 1000000000;

using namespace std;

bool comp(string& s1, string& s2) {
	if (s1.size() == s2.size()) {
		return s1 < s2;
	}
	return s1.size() < s2.size();
}

string bfs(int s, int d) {
	psi now = {s,""};
	mp[s] = "0";
	que.push(now);

	int ti = 0;
	while (que.size()) {
		int cnt = que.size();

		while (cnt--) {
			now = que.front(); que.pop();

			if (now.first == d) return mp[now.first];

			string op; long long num;
			tie(num, op) = now;

			for (int i = 0; i < 4; i++) {
				psi next = now;
				next.second += oper[i];
				
				switch (i) {
				case 0: next.first *= next.first; break;
				case 1: next.first += next.first; break;
				case 2: next.first -= next.first; break;
				case 3: if (next.first) next.first /= next.first; break;
				}

				if (next.first < 0 || next.first > INF) continue;
				if (mp[next.first].size()==0 ||comp (next.second, mp[next.first])) {
					mp[next.first] = next.second;
					que.push(next);
				}
			}
		}
		ti++;
	}
	return "-1";
}

int BOJ14395() {
	int s, d;
	cin >> s >> d;
	cout << bfs(s, d);
	return 0;
}
