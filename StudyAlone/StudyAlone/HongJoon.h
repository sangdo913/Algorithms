#pragma once
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

bool HongJoon_Min(long long &x, long long &y)
{
	bool result = x > y;

	if (result)
	{
		int temp = y;
		y = x; 
		x = temp;
	}
	return result;
}
void HongJoon()
{
	long long N, T;
	long long dp[102][2];
	cin >> T;
	for (long long t = 1; t <= T; t++)
	{
		long long A, B;
		cin >> A >> B;
		bool is_change = HongJoon_Min(A, B);
		// lower is A
		memset(dp, 0, sizeof(dp));
		long long result1 = -1, result2 = -1;
		int ind = 1;
		dp[0][0] = 1;
		dp[0][1] = 0;
		dp[1][0] = 0;
		dp[1][1] = 1;
		while (B !=1)
		{
			ind++;
			dp[ind][0] = dp[ind - 2][0] - dp[ind - 1][0] * (B / A);
			dp[ind][1] = dp[ind - 2][1] - dp[ind - 1][1] * (B / A);

			int store = A;
			A = B%A;
			B = store;
		}

		if (!is_change)
		{
			int temp = dp[ind - 1][0];
			dp[ind - 1][0] = dp[ind - 1][1];
			dp[ind - 1][1] = temp;
		}
		cout << "#" << t << " " << dp[ind-1][0] << " " << dp[ind-1][1] << "\n";
	}

}