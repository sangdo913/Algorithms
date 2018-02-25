#pragma once
#include<iostream>

using namespace std;

int Rich_goods[1000000];

int RichProject()
{
	long long maxCost = 0,T,N;
	long long maxIndex,start = 0;
	long long money;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		maxCost = 0;
		money = 0;
		maxIndex = 0;
		start = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> Rich_goods[i];
			if (maxCost  <= Rich_goods[i])
			{
				maxCost = Rich_goods[i];
				maxIndex = i;
			}
		}
		while (start < N)
		{
			long long price = 0, earn,cnt = 0;
			for (; start < maxIndex; start++)
			{
				price += Rich_goods[start];
				cnt++;
			}
			earn = cnt*maxCost - price;
			maxCost = 0;
			start = maxIndex + 1;
			money += earn;
			for (int i = start; i < N; i++)
			{
				if (Rich_goods[i] >= maxCost)
				{
					maxIndex = i;
					maxCost = Rich_goods[i];
				}
			}
		}

		cout << '#' << tc << ' ' << money << '\n';
	}
	return 0;
}