#pragma once
#include<iostream>
using namespace std;

int groups[2][45000];
int glen[2];

int Codeforce508B() {
	int n;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;

	if (n < 3) {
		printf("No\n");
		return 0;
	}
	cout << "Yes\n";

	if (n % 2) {
		groups[0][glen[0]++] = n;
		for (int i = 1; i < n; i++) {
			groups[1][glen[1]++] = i;
		}
		cout << 1 << ' ' << n << '\n';
		cout << glen[1] << ' ';
		for (int i = 0; i < glen[1]; i++) {
			cout << groups[1][i] << ' ';
		}
		cout << '\n';
		return 0;
	}
	else {
		cout << 2 << ' ' << 1<<' '  << n << '\n';
		cout << n-2 << ' ';
		for (int i = 2; i < n; i++) {
			cout << i << ' ';
		}
		cout << '\n';

		return 0;
	}
	return 0;
}