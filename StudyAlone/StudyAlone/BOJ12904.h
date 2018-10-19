#pragma once
//https://www.acmicpc.net/problem/12904
//BOJ 12904 A¿Í B
#include<iostream>
#include<string>

using namespace std;

string a, b;
int BOJ12904() {
	cin >> a >> b;

	while (a.size() != b.size()) {
		int c = b.back();
		b.pop_back();
		if (c == 'B') b = string(b.rbegin(), b.rend());
	}
	cout << (a == b);
	
	return 0;
}