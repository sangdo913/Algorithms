//https://www.acmicpc.net/problem/2789
//´ÙÀÌ¾ó
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int conv[256];
char nums[16];

int BOJ5622() {
	for (int i = 0; i < 26; i++) {
		conv[i + 'A'] = i / 3 + 3;
	}

	conv['S'] = 8;
	conv['V'] = 9;
	conv['Y'] = 10;
	conv['Z'] = 10;

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> nums;
	int len = strlen(nums);

	int t = 0;
	for (int i = 0; i < len; i++) {
		t += conv[nums[i]];
	}
	cout << t << endl;
	
	return 0;
}
