#pragma once
#include<iostream>

using namespace std;
long long a, b;
char nums[19];
int EduCodeforce50A() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> a >> b;

	long long h1 = b / a;
	if (b%a) h1++;

	cout << h1 << '\n';
	return 0;
}