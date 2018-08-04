#pragma once
#include<iostream>
#include<cstring>

using namespace std;

struct ChickenInfo
{
	int map[50][50];
	int n;
	int m;
	typedef struct Cod{ int r,c; } cod;
	int cNum, pNum;
	cod company[13];
	cod people[100];

	int abs(int i)
	{
		return i > 0 ? i : -i;
	}

	int min(int i1, int i2)
	{
		return i1 < i2 ? i1 : i2;
	}

	int getDistance(int num, int select)
	{
		int ind = 0;
		int dist = 99999;

		while (select)
		{
			if (select & 1)
			{
				int tempDistance;
				tempDistance = abs(people[num].r - company[ind].r) + abs(people[num].c - company[ind].c);
				dist = min(tempDistance, dist);
			}
			select >>= 1;
			ind++;
		}

		return dist;
	}

	int getZeros(int n)
	{
		int res = 0;
		while ((n & 1) == 0)
		{
			res++;
			n >>= 1;
		}
		return res;
	}

	int getAllDist()
	{
		int visit = (1 << m) - 1;
		int max = (1 << cNum);
		int minDist = 999999;

		while (visit < max)
		{
			int temp = visit | (visit - 1);
			int dist = 0;
			for (int i = 0; i < pNum; i++)
			{
				dist += getDistance(i, visit);
			}

			minDist = min(minDist, dist);
			visit = (temp + 1) | (((~temp & -~temp) - 1) >> (getZeros(visit) + 1));
		}

		return minDist;
	}

	void init()
	{
		memset(map, 0, sizeof(map));
		pNum = cNum = 0;

		cin >> n >> m;


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 1)
				{
					people[pNum].r = i;
					people[pNum].c = j;
					pNum++;
				}
				else if (map[i][j] == 2)
				{
					company[cNum].r = i;
					company[cNum].c = j;
					cNum++;
				}
			}
		}

	}
}ChickInfo;

int Chicken()
{
	ChickInfo.init();
	int res = ChickInfo.getAllDist();
	cout << res << '\n';
	return 0;
}