//https://www.acmicpc.net/problem/12886
//BOJ12886 µ¹ ±×·ì
#pragma once
#include<iostream>
#include<map>
#include<tuple>
#include<queue>

using namespace std;


struct INFO {
	int a, b, c;
	INFO(int a, int b, int c) :a(a), b(b), c(c) {}
	INFO() :a(0), b(0), c(0) {}
};

map<int, bool> visit;
queue<INFO> que;

void change(int &a, int&b) {	
	a = a - b;
	b <<= 1;
}

void swap(int &a, int&b) {
	int t = a;
	a = b;
	b = t;
}

void mysort(INFO &now) {
	if (now.a < now.b) {
		swap(now.a, now.b);
	}

	if (now.b < now.c) {
		swap(now.b, now.c);
	}

	if (now.a < now.b) {
		swap(now.a, now.b);
	}
}

bool isout(int dol[2]) {
	return dol[0] > 1000 || dol[1] > 1000;
}

int key(INFO now) {
	int res =  now.a * 1000000;
	res += now.b * 1000;
	res += now.c;
	return res;
}

bool bfs(INFO now) {
	mysort(now);
	visit[key(now)] - true;

	que.push(now);

	while (!que.empty()) {
		now = que.front();
		que.pop();

		if (now.a == now.b && now.b == now.c) return true;
		

		int dol[2] = { now.a, now.b };
		if (dol[0] != dol[1]) {
			change(dol[0], dol[1]);
			INFO next(dol[0], dol[1], now.c);
			mysort(next);
			if (!isout(dol) && !visit[key(next)]) {
				visit[key(next)]= true;
				que.push(next);
			}
		}
		dol[0] = now.a;
		dol[1] = now.c;

		if (dol[0] != dol[1]) {
			change(dol[0], dol[1]);
			INFO next(dol[0], now.b, dol[1]);
			mysort(next);
			if (!isout(dol) && !visit[key(next)]) {
				visit[key(next)] = true;
				que.push(next);
			}
		}
		dol[0] = now.b;
		dol[1] = now.c;
		if (dol[0] != dol[1]) {
			change(dol[0], dol[1]);
			INFO next(dol[0], dol[1], now.a);
			mysort(next);
			if (!isout(dol)&& !visit[key(next)]) {
				visit[key(next)] = true;
				que.push(next);
			}
		}
	}
	return false;
}

int BOJ12886() {
	int a, b, c;
	cin >> a >> b >> c;
	
	cout << bfs({ a,b,c });

	return 0;
}