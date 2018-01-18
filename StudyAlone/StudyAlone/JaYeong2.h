#pragma once
#include<iostream>
#include<cstring>

using namespace std;

bool JaYeong_Village[9][9];


void JaYeong2()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		memset(JaYeong_Village, 0, sizeof(JaYeong_Village));
		int result = 0;
		char input;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				cin >> input;
				JaYeong_Village[i][j] = input == '1';
			}

		cout << '#' << tc << ' ' << result << endl;
	}
}