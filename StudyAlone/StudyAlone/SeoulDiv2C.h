#pragma once
#include<iostream>
using namespace std;

int SeoulDiv2C() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int X, N;

	cin >> X >> N;
	if (N == 1 && X < 0) {
		cout << "INFINITE"; return 0;
	}
	if (N == 1 && X >= 0) {
		cout << "0"; return 0;
	}

	if (N % 2) {
		cout << "ERROR"; return 0;
	}

	if (N == 0) {
		if (X > 0) {
			cout << "INFINITE"; return 0;
		}
		else {
			cout << "0"; return 0;
		}
	}
	
	int mi = N / 2;
	int cnt = 0;
	while ((X -= mi) > 0) {
		
		cnt++;
	}
	cout << cnt;
	return 0;
}
