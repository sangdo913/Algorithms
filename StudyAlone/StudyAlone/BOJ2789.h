//https://www.acmicpc.net/problem/2789
//유학금지
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

char del[10] = "CAMBRIDGE";
char str[101];
char res[101];
int rlen;
int BOJ2789() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> str;
	
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		bool deleted = false;
		for (int j = 0; j < 10; j++) {
			if (str[i] == del[j]) {
				deleted = true;
				break;
			}
		}

		if (deleted) continue;
		
		res[rlen++] = str[i];
	}
	
	res[rlen] = 0;
	cout << res;
	return 0;
}