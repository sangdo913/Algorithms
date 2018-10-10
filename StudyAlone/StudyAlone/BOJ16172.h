//https://www.acmicpc.net/problem/16172
//BOJ16172 나는 친구가 적다
#pragma once
#include<iostream>
const int MOD = 10003;

using namespace std;

int len(char* str) {
	int idx = 0;
	while (*str) {
		str++;
		idx++;
	}
	return idx;
}

bool convstr(char* str1, char* str2, int l) {
	int idx = 0;
	while (idx < l && *str1 && *str2 && *str1 == *str2) {
		str1++; str2++;
		idx++;
	}
	return *str1 == *str2;
}

char s[1000001];
char convs[1000001];
char t[1000001];
int conv[256];

int pow(int n) {
	int res = 1;
	int mul = 2;
	while (n ) {
		if (n & 1) {
			res *= mul;
			res %= 10003;
		}
		mul *= mul;
		mul %= 10003;
		n >>= 1;
	}
	return res;
}

int BOJ16172() {
	int h;
	int ls, lt, convl = 0;

	cin >> s >> t;
	ls = len(s);
	lt = len(t);
	
	int num = 0;
	for (int i = 'A'; i <= 'Z'; i++) {
		conv[i] = num++;
	}
	for (int i = 'a'; i <= 'z'; i++) {
		conv[i] = num++;
	}


	for (int i = 0; i < ls; i++) {
		if (s[i] < '0' || s[i] > '9') {
			convs[convl++] = s[i];
		}
	}

	h = 0;
	for (int i = 0; i < lt; i++) {
		h <<= 1;
		h += conv[t[i]];
		h %= MOD;
	}
	
	int ch = 0;
	for (int i = 0; i < lt; i++) {
		ch <<= 1;
		ch += conv[convs[i]];
		ch %= MOD;
	}

	bool find = convstr(convs, t, lt);

	int st = 0;
	for (int i = lt; i < convl && !find; i++) {
		ch <<= 1;
		ch = ch + MOD + conv[convs[i]] - (conv[convs[st]] * pow(lt)) % MOD;
		ch %= MOD;
		if (ch == h) {
			find = convstr(convs + st+1, t, lt);
		}
		st++;
	}
	cout << find;
	return 0;
}
