//https://www.acmicpc.net/problem/10986
//BOJ 10986 나머지 합
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int rm[1000];
int arr[1000000];

int BOJ10986() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n, m;
	cin >> n >> m;
	long long res = 0;

	for (int i = 0; i < n; i++) cin >> arr[i];

	int p = 0;

	for (int i = 0; i < n; i++) {
		p =(p+ m - (arr[i] % m))%m;
		
		rm[(p + arr[i]) % m]++;
		res += rm[p];
	}

	cout << res;

	return 0;
}
