#pragma once
#include<iostream>

using namespace std;
inline long long Predict_2X1(long long num)
{
	return (num << 1) + 1;
}
inline long long Predict_2X(long long num)
{
	return (num << 1);
}
inline int Predict_Get_MSB(long long num)
{
	long long i = (long long)1<<60;
	int ret = 60;
	while (i > num)
	{
		i >>= 1;
		ret--;
	}
	return ret;
}
int Predict()
{
	enum Player {Alice = 0, Bob = 1};
	long long value, gameValue;
	int T, msb;
	typedef long long(*func)(long long num);
	func playerFunc[2];
	const char winner[2][6] = { "Alice", "Bob" };
	Player p;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> value;
		gameValue = 1;
		msb = Predict_Get_MSB(value);
		p = msb & 1 ? Alice : Bob;
		playerFunc[Alice] = p == Alice ? Predict_2X : Predict_2X1;
		playerFunc[Bob] = p == Bob ? Predict_2X : Predict_2X1;
		p = Alice;
		while (gameValue <= value)
		{
			switch (p)
			{
			case Alice:
				gameValue = playerFunc[Alice](gameValue);
				p = Bob;
				break;
			case Bob:
				gameValue = playerFunc[Bob](gameValue);
				p = Alice;
				break;
			}
		}

		cout << '#' << tc << ' ' << winner[p] << '\n';
	}

	return 0;
}