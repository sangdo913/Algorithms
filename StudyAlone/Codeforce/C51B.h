#pragma once
#include<iostream>
#include<vector>

using namespace std;

int C51B() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long l, r;
	cin >> l >> r;

	cout << "YES\n";
	long long st = l;
	for (int i = 0; i < (r - l + 1) / 2; i++) {
		cout << st << ' ' << st + 1 << '\n';
		st += 2;
	}
	return 0;
}
