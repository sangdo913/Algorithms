#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

int LCS_MAX(int x, int y)
{
	return x > y ? x : y;
}

void LCS()
{
	int T;
	int **lcs;
	lcs = (int**)malloc(sizeof(int*)*1001);

	for (int i = 0; i < 1001; i++)
	{
		lcs[i] = (int*)malloc(sizeof(int) * 1001);
	}

	string a, b;
	cin >> T;
	for (int k = 1; k <= T; k++)
	{
		cin >> a >> b;
		for (int i = 0; i < 1001; i++)
		{
			if (i == 0)
				for (int j = 1; j < 1001; j++) lcs[i][j] = 0;
			lcs[i][0] = 0;
		}
		for (int i = 1; i <= a.size(); i++)
		{
			for (int j = 1; j <= b.size(); j++)
			{
				if (a[i - 1] == b[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
				else
				{
					lcs[i][j] = LCS_MAX(lcs[i - 1][j], lcs[i][j - 1]);
				}
			}
		}

		cout << "#" << k << " " << lcs[a.size()][b.size()] << endl;
	}

	for (int i = 0; i < 1001; i++)
	{
		free(lcs[i]);
	}
	free(lcs);
}