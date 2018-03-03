#pragma once
#include<iostream>

using namespace std;

bool Possible_check[10001] = { true };
int Possible_array[100];
int PossibleScore()
{
	int T, N;
	int res,max;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		max = res = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> Possible_array[i];
			max += Possible_array[i];

		}
		for (int i = 1; i <= max; i++) Possible_check[i] = false;
		for (int i = 0; i < N; i++)
		{
			for (int i2 = max; i2--;)
			{
				if (Possible_check[i2])
				{
					Possible_check[i2 + Possible_array[i]] = true;
				}

			}
		}

		for (int i = 0; i <= max; i++)
		{
			res += Possible_check[i];
		}
		cout << '#'<< tc << ' ' << res << endl;
	}
	return 0;
}