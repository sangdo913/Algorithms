#pragma once
#include<iostream>
#include<cstdio>
#include<string.h>
#include<stdint.h>

using namespace std;

struct Cooker_Info
{
	int n;
	int map[16][16];
	bool selected[16][16];
	int max;
	void init()
	{
		memset(map, 0, sizeof(map));
		memset(selected, false, sizeof(selected));
		max = INT32_MAX;

		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &map[i][j]);
			}
	}
	int abs(int i1)
	{
		return i1 > 0 ? i1 : -i1;
	}
	int getMin(int selected)
	{
		int res = 0;
		int res2 = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = i+1; j < n ; j++)
			{
				if ((selected & (1 << i)) && (selected & (1 << j)))
				{
					res += map[i][j];
					res += map[j][i];
				}
				if (!(selected & (1 << i)) && !(selected & (1 << j)))
				{
					res2 += map[i][j];
					res2 += map[j][i];
				}
			}
		}

		return abs(res-res2);
	}
	int getMax(int i1, int i2)
	{
		return i1 < i2 ? i1 : i2;
	}

	void celcious(int n, int c, int selected)
	{
		if (n == c || c == 0)
		{
			selected |= (1 << c) - 1;
			
			max = getMax(max,getMin(selected));
			return;
		}

		celcious(n - 1, c, selected);

		selected |= 1<<n-1;

		celcious(n - 1, c - 1, selected);
	}
}Cooker_info;


int Cooker()
{
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++)
	{
		Cooker_info.init();
		Cooker_info.celcious(Cooker_info.n, Cooker_info.n >> 1, 0);
		printf("#%d %d\n", tc,Cooker_info.max);
	}
	return 0;
}