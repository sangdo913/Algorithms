#pragma once
#include<iostream>

using namespace std;

int PascalTriangle()
{
	int pas[10][10];

	int t;
	cin >> t;
	
	for (int i = 0; i < 10; i++)
	{
		pas[i][0] = 1;
		pas[i][i] = 1;
	}

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < i; j++)
		{
			pas[i][j] = pas[i - 1][j - 1] + pas[i - 1][j];
		}
	}
	
	for (int tc = 1; tc <= t; tc++)
	{
		int n;
		cin >> n;
		cout << '#' << tc << '\n';
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				cout << pas[i][j] << ' ';
			}
			cout << '\n';
		}
	}
	return 0;
}