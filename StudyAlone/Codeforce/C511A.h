#pragma once
#include<iostream>
using namespace std;

int C511A() {
	int n;
	cin >> n;

	int share = n / 3;
	if (share %3 == 0) {
		if (n % 3 == 1) {
			cout << share + 1 << ' ' << share - 1 << ' ' << share + 1;
		}
		else if (n % 3 == 2) {
			cout << share + 1 << ' ' << share - 1 << ' ' << share + 2;
		}
		else {
			cout << share + 1 << ' ' << share + 1 << ' ' << share - 2;
		}
	}
	else if (share % 3 == 1) {
		if (n % 3 == 0) {
			cout << share << ' ' << share << ' ' << share;
		}
		else if (n % 3 == 1) {
			cout << share << ' ' << share << ' ' << share + 1;
		}
		else {
			cout << share <<  ' ' << share + 1 << ' ' << share + 1;
		}
	}
	else {
		if (n % 3 == 1) {
			cout << share + 2 << ' ' << share << ' ' << share - 1;
		}
		else {
			cout << share << ' ' << share << ' ' << share + (n % 3);
		}
	}
	return 0;
}
