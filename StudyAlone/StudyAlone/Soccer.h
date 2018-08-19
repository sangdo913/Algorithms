#pragma once
#include<iostream>

using namespace std;

void Soccer()
{
	enum Team { A = 0, B = 1, size };
	//team, time, goal
	long long double posibility[2][30][31];
	long long double possible[2];
	const int notPrime[21] = { 0,1,4,6,8,9,10,12,14,15,16,18,20,21,22,24,25,26,27,28,30 };

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> possible[Team::A] >> possible[Team::B];

		for (int i = 0; i < Team::size; i++) possible[i] /= 100.0;
		for (int i = 0; i < Team::size; i++)
		{
			for (int j = 0; j < 30; j++)
				for (int k = 0; k < 31; k++)
					posibility[i][j][k] = 0;
		}

		posibility[Team::A][0][0] = 1.0 - possible[Team::A];
		posibility[Team::A][0][1] = possible[Team::A];

		posibility[Team::B][0][0] = 1.0 - possible[Team::B];
		posibility[Team::B][0][1] = possible[Team::B];

		for (int team = Team::A; team < Team::size; team++)
			for (int time = 1; time < 30; time++)
			{
				for (int goal = 0; goal < 31; goal++)
				{
					posibility[team][time][goal] += posibility[team][time - 1][goal] * (1 - possible[team]);
					if (goal > 0)posibility[team][time][goal] += posibility[team][time - 1][goal - 1] * possible[team];
				}
			}
		long long double result = 0;
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
				result += posibility[Team::A][29][notPrime[i]] * posibility[Team::B][29][notPrime[j]];
		}
		cout.setf(ios::fixed);
		cout.precision(5);
		cout << '#' << tc << ' ' << 1.0 - result << endl;
	}
}