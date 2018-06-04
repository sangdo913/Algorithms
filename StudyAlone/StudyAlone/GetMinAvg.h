#pragma once
#include<iostream>

using namespace std;

int GetMinAvg()
{
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++)
	{
		int res = 0;
		int num, max = -1, min = 100000;

		for (int i = 0; i < 10; i++)
		{
			cin >> num;
			min = num < min ? num : min;
			max = num > max ? num : max;
			res += num;
		}

		cout << '#' << tc << ' ' << (res - max - min + 4) / 8 << '\n';
	}
	return 0;
}