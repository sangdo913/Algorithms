//https://www.acmicpc.net/problem/14238
//BOJ 14238 출근기록
#pragma once
#include<iostream>
#include<string>

using namespace std;

int conv[256];
int cache[3][3][51][51][51];
string s;

int make(int prev1, int prev2, int a, int b, int c) {
	if (a == 0 && b == 0 && c == 0) {
		return 1;
	}

	int& res = cache[prev1][prev2][a][b][c];
	if (res) return res;

	if (a > 0) {
		s.push_back('A');
		res = make(prev2, 0, a - 1, b, c);
		if (res == 1) return 1;
		s.pop_back();
	}

	if (b > 0 && prev2 != 1) {
		s.push_back('B');
		res = make(prev2, 1, a, b - 1, c);
		if (res == 1) return 1;
		s.pop_back();
	}

	if (c > 0 && prev1 != 2 && prev2 != 2) {
		s.push_back('C');
		res = make(prev2, 2, a, b, c - 1);
		if (res == 1)return 1;
		s.pop_back();
	}

	return res = -1;
}

int BOJ14238() {
	conv['A'] = 0;
	conv['B'] = 1;
	conv['C'] = 2;

	string in;
	cin >> in;

	int nums[3] = {};
	for (int i = 0; i < in.size(); i++) {
		nums[conv[in[i]]]++;
	}

	cout << (make(0,0,nums[0],nums[1], nums[2]) != -1 ? s : "-1");

	return 0;
}
