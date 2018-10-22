//https://www.acmicpc.net/problem/1305
//BOJ 1305 ±¤°í
#pragma once
#include<iostream>
#include<string>
#include<algorithm>


using namespace std;
string s;

int kmp[1000002];

int mk() {
	int j = 0;
	kmp[0] = -1;

	for (int i = 1; i < s.size(); i++) {
		kmp[i] = j;

		while (j != -1 && s[i] != s[j]) {
			j = kmp[j];
		}
		j++;
	}

	j = kmp[s.size() - 1];
	while (j != -1 && s[s.size() - 1] != s[j]) {
		j = kmp[j];
	}
	j++;
	return s.size() - j;
}

int BOJ1305() {
	int n; 
	cin >> n;
	cin >> s;

	cout << mk();

	return 0;
}
