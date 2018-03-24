#pragma once
#include<iostream>

using namespace std;

void SpaceGod()
{
	ios::ios_base::sync_with_stdio(false);
	long long N, M;
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >>M;
		long long result_index = N % (M * 2);
		long long result;
		long long prev_prev = 0, prev = 1;
		for (int i = 3; i <= result_index; i++)
		{
			result = (((i - 1) % M)*(prev_prev + prev)) % M;
			prev_prev = prev;
			prev = result;
		}
		if (result_index == 1) result = prev_prev;
		else if (result_index == 2) result = prev;
		cout << '#' << tc << ' ' << (result*result)%M << endl;
	}
}