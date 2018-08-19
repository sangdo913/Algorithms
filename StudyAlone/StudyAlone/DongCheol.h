#pragma once
#include<iostream>

using namespace std;

long long double DongCheol_ARR[16][16];
long long double DongCheol_visit[16][1<<16];

inline long long double DongCheol_MAX(long long double x1, long long double x2)
{
	return x1 > x2 ? x1 : x2;
}

long long double DongCheol_GetMax(int length, int length_max, long long visit,int x)
{
	long long double &result = DongCheol_visit[x][visit];
	if (result != 0) return result;
	visit |= 1 << x;
	if (visit == (1<<length_max) -1) return DongCheol_ARR[length][x];

	for (int i = 0; i < length_max; i++)
	{
		if ((visit >> i) & 1) continue;
		result = DongCheol_MAX(result, DongCheol_ARR[length][x]*DongCheol_GetMax(length + 1, length_max, visit, i));
	}

	visit ^= 1 << x;
	return result;
}
void DongCheol()
{
	std::ios::sync_with_stdio(false);
	int T,N;
	long long double in;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		for (int i = 0; i != N; i++)
		{
			for (int j = 0; j < 1 << 16; j++)
			DongCheol_visit[i][j] = 0;
		}
		//in;
		for (int row  =N; row--;)
		{
			for (int col = N; col--;)
			{
				cin >> DongCheol_ARR[row][col];
				DongCheol_ARR[row][col] /= 100.0;
			}
		}
		long long double result = 0;
		for (int i = 0; i!=N;i++)
			result = DongCheol_MAX(result,DongCheol_GetMax(0, N, 0, i));

		cout.setf(ios::fixed);
		cout.precision(6);
		cout << '#' << tc << ' ' << result*100.0 << endl;
	}
}