//https://www.acmicpc.net/problem/12871
//BOJ 12871 무한 문자열
#pragma once

#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int GCD(int a, int b) {
	int r; 
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
int BOJ12871() {
	string s1, s2;
	
	cin >> s1 >> s2;

	int g = GCD(s1.size(), s2.size());
	int lcd = s1.size()*s2.size() / g;

	string temp = s1;
	while (s1.size() != lcd) {
		s1 += temp;
	}

	temp = s2;
	while (s2.size() != lcd) {
		s2 += temp;
	}
	
	cout << (s1 == s2);
	return 0;
}
