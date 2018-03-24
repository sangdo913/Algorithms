#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>

using namespace std;

void JungTriangle()
{
	int T;
	long long A, B;
	string a;
	long long prime = 1000000007;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> A;
		cout << '#' << tc << ' ' << A*A / B / B << endl;
	}
}