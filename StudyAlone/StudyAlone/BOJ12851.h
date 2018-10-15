//https://www.acmicpc.net/problem/12851
//BOJ 12851 ¼û¹Ù²ÀÁú2
#pragma once
#include<iostream>
#include<queue>

using namespace std;

int pos[100001];
int order[100001];

int s, d;
queue<int> que;

int bfs() {
	que.push(s);
	pos[s] = 1;
	order[s] = 0;

	
	int ti = 0;
	while (que.size()) {
		int cnt = que.size();
		
		while (cnt--) {
			int now = que.front(); que.pop();
			if (now == d) return ti;

			
			if (now - 1 >= 0) {
				if (pos[now-1] == 0 || order[now-1] == order[now] + 1) {
					order[now - 1] = order[now] + 1;
					if (pos[now - 1] == 0) que.push(now - 1);
					pos[now - 1] += pos[now];
				}
			}

			if (now * 2 <= 100000 && (pos[now*2] == 0 || order[now*2] == order[now] + 1)) {
				if(pos[now*2] == 0) que.push(now * 2);
				pos[now * 2] += pos[now];
				order[now * 2] = order[now] + 1;
			}

			if (now + 1 <= 100000 && (pos[now+1] == 0 || order[now+1] == order[now] +1)) {
				if (pos[now + 1] == 0) que.push(now + 1);
				pos[now + 1] += pos[now];
				order[now + 1] = order[now] + 1;
			}
		}
		ti++;
	}

	return -1;
}
int BOJ12851() {
	cin >> s >> d;

	cout << bfs() << endl;
	cout << pos[d];
	int x = 0;

	return 0;
}
