#pragma once
#include<iostream>

using namespace std;

int ZigZagNumber()
{
	int zigzag[11];
	zigzag[1] = 1;
	bool isMinus = true;
	for (int i = 2; i < 11; i++)
	{
		zigzag[i] = isMinus ? zigzag[i - 1] - i : zigzag[i - 1] + i;
		isMinus = !isMinus;
	}

	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		int n;
		cin >> n;
		cout << '#' << tc << ' ' << zigzag[n] << '\n';
	}
	return 0;
}