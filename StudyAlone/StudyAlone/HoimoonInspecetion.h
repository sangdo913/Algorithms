#pragma once
#include<iostream>
#include<string>

using namespace std;

int HoimoonInspection()
{
	string str;
	int t, size;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> str;

		size = str.size();
		bool isHoiMoon = true;

		for (int i = 0; i < (size >> 1); i++)
		{
			isHoiMoon &= str[i] == str[size - 1 - i];
		}
		cout << '#' << tc << ' ' << isHoiMoon << '\n';
	}


	return 0;
}