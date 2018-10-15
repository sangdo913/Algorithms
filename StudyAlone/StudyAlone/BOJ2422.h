//https://www.acmicpc.net/problem/2422
//BOJ 2422 �������� ��Ż���ƿ� ���� ���̽�ũ���� ��Դµ�
#pragma once
#include<iostream>

using namespace std;

int n, m;
bool no[201][201];
int selected[3];
int res = 0;

bool check(int c, int select) {
	for (int i = 0; i < select; i++) {
		if (no[c][selected[i]]) return false;
	}
	return true;
}

void dfs(int i, int select) {
	if (select == 3) {
		res++;
		return;
	};

	if (i > n) return;


	dfs(i + 1, select);

	if (check(i, select)) {
		selected[select] = i;
		dfs(i + 1, select + 1);
	}
}

int BOJ2422() {
	cin >> n >> m;

	while (m--) {
		int f, t;
		cin >> f >> t;
		no[f][t] = true;
		no[t][f] = true;
	}

	dfs(1, 0);
	cout << res;
	
	return 0;
}