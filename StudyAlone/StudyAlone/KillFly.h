#pragma once
#include<iostream>

using namespace std;

int KillFly()
{
	int map[15][15];
	int m, n,t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cin >> n >> m;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cin >> map[i][j];
		}

		int maskMax = 0;

		for (int i = 0; i <= n - m; i++)
		{
			for (int j = 0; j <= n - m; j++)
			{
				int mask = 0;
				for (int r = 0; r < m; r++)
				{
					for (int c = 0; c < m; c++)
					{
						mask += map[i + r][j + c];
					}
				}
				maskMax = maskMax < mask ? mask : maskMax;
			}
		}

		cout << '#' << tc << ' ' << maskMax << '\n';
	}

	return 0;
}