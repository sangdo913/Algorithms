#pragma once
#include<iostream>

using namespace std;

void WaveClass()
{
	long long Dp[101] = { 0,1,1,1,2,2 };
	int T, N ;
	for (int i = 6; i < 101; i++)
	{
		Dp[i] = Dp[i - 1] + Dp[i - 5];
	}

	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		cout << '#' << tc << ' ' << Dp[N] << endl;
	}
}