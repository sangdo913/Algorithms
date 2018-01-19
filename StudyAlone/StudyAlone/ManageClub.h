#pragma once
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>

using namespace std;

int ManageClub_Conv(char in)
{
	return (int)(in - 'A');
}

long long ManageDP[10001][1<<4];

void ManageClub()
{
	int T;
	long long prime = 1000000007;
	cin >> T;
	const int A = 1;
	const int B = 1 << 1;
	const int C = 1 << 2;
	const int D = 1 << 3;
	for (int tc = 1; tc <= T; tc++)
	{
		long long result = 0;
		memset(ManageDP, 0, sizeof(ManageDP));
		//string in;
		char in[10001];
		cin >> in;
		int in_size = strlen(in);
		ManageDP[0][A] = 1;

		//DP
		for (int i = 0; i < in_size; i++)
		{
			int manage = 1 <<ManageClub_Conv(in[i]);
			for (int j = 1; j < 16; j++)
			{
				for (int k = 1; k < 16; k++)
				{
					if (!(j&k) || !(k&manage)) continue;
					ManageDP[i + 1][k] = (ManageDP[i+1][k] + ManageDP[i][j])% 1000000007;
				}
			}
		}

		for (int i = 0; i < 16; i++)
			result = (result+ManageDP[in_size][i]) % 1000000007;
		cout << '#' << tc << ' ' << result << endl;
	}
}