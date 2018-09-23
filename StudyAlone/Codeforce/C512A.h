#pragma once
#include<iostream>

using namespace std;

int C512A() {
	int n;

	int hard = false;
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		int in;
		cin >> in;
		hard |= in;
	}
	cout << (hard ? "HARD" : "EASY"); 

	return 0;
}
