#pragma once
#include<cstdio>
#include<deque>

#include<string>
#include<iostream>
using namespace std;

int CodeforceAIMB() {
	string str[2];

	int n, m;
	scanf("%d %d\n", &n, &m);

	for (int i = 0; i < n; i++) {
		str[0].push_back('1');
	}
	
	while (str[1].size() + 1 < str[0].size()) {
		str[1].push_back('8');
	}
	str[1].push_back('9');
	cout << str[0] << '\n';
	cout << str[1] << '\n';
	return 0;
}