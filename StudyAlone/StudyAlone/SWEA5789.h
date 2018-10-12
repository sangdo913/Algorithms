//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWYygN36Qn8DFAVm&categoryId=AWYygN36Qn8DFAVm&categoryType=CODE
//SWEA5789 현주의 상자 바꾸기O
#pragma once
#include<iostream>

using namespace std;

int arr[1001];
int n;
void set(int n) {
	for (int i = 1; i <= n; i++) arr[i] = 0;
}

void query(int i,int s, int e) {
	for (int idx = s; idx <= e; idx++) {
		arr[idx] = i;
	}
}

int SWEA5789() {
	int n, t,q;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> q;
		for(int i = 1; i <= q; i++){
			int s, e;
			cin >> s >> e;
			query(i, s, e);
		}

		cout << '#' << tc << ' ';
		for (int i = 1; i <= n; i++) cout << arr[i] << ' ';
		cout << '\n';

		set(n);
	}

	return 0;
}