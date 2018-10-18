//https://www.acmicpc.net/problem/12969 
//BOJ 12969 ABC
#pragma once
#include<iostream>
#include<cstdio>
#include<string>

using namespace std;

char cache[15*29+1][31][31][31];
int n, k;
string s;


char canMake(int len, int a, int b, int c, int cnt) {
	if (n == len) {
		if (k == cnt) {
			return cache[cnt][a][b][c] = 1;
		}
		else return cache[cnt][a][b][c] = -1;
	}

	if (cnt > k) return cache[cnt][a][b][c] = -1;

	char& res = cache[cnt][a][b][c];

	if (res != 0) return res;


	len++;
	s += 'A';
	res = canMake(len, a + 1, b, c, cnt);
	if (res == 1) return 1;

	s.pop_back();
	s += 'B';
	res = canMake(len, a, b + 1, c, cnt + a);
	if (res == 1) return 1;
	
	s.pop_back();
	s += 'C';
	res = canMake(len, a, b, c + 1, cnt + a + b);
	if (res == 1) return 1;

	s.pop_back();

	return res=-1;
}

int BOJ12969() {
	cin >> n >> k;

	cout << (canMake(0, 0, 0, 0, 0) == 1 ? s : "-1");

	return 0;
}
