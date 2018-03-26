#pragma once
#include<iostream>
#include<string.h>

using namespace std;

struct HomeBangBeom_Info
{
	int n; int m;
	int map[22][22];
	bool visit[22][22];
	int num;
	int getCost(int c)
	{
		return c*c + (c - 1)*(c - 1);
	}

	void init()
	{
		memset(map, -1, sizeof(map));
		num = 0;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				scanf("%d", &map[i][j]);
				num += map[i][j];
			}
	}

	int getMax(int x, int y, const int cnt)
	{
		int num = 0;
		if (cnt == 0) return 0;
		for (int c = 1; c < cnt; c++)
		{
			if (map[y][x + c] == -1) break;
			else if (map[y][x + c]) ++num;
		}

		for (int c = 1; c < cnt; c++)
		{
			if (map[y][x - c] == -1) break;
			else if (map[y][x - c]) num++;
		}

		if (map[y][x])num++;

		if (!visit[y - 1][x] && map[y - 1][x] != -1)
		{
			visit[y - 1][x] = true;
			num += getMax(x, y - 1, cnt - 1);
			visit[y - 1][x] = false;
		}

		if (!visit[y + 1][x] && map[y + 1][x] != -1)
		{
			visit[y + 1][x] = true;
			num += getMax(x, y + 1, cnt - 1);
			visit[y + 1][x] = false;
		}

		return num;
	}

	int max(int i1, int i2)
	{
		return i1 > i2 ? i1 : i2;
	}

}HomeBangBeom_info;


int HomeBangbeom()
{
	int t, cost, house;
	int res;
	scanf("%d", &t);
	HomeBangBeom_Info& info = HomeBangBeom_info;
	for (int tc = 1; tc <= t; tc++)
	{
		info.init();
		int max = -1;
		res = 0;

		for (int size = 1; max != info.num; size++)
		{
			for (int i = 1; i <= info.n; i++)
			{
				for (int j = 1; j <= info.n; j++)
				{
					info.visit[i][j] = true;
					house = info.getMax(j, i, size);
					info.visit[i][j] = false;

					max = info.max(max, house);

					cost = house * info.m - info.getCost(size);
					if (cost >= 0)
					{
						res = info.max(res, house);
					}
				}
			}
		}

		printf("#%d %d\n", tc, res);
	}
	return 0;
}