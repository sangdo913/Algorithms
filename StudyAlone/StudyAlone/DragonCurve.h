#pragma once
#include<iostream>
#include<cstring>

using namespace std;

struct DragonCurveInfo
{
	int map[101][101];

	typedef struct Cod { int r, c; } cod;

	const int dr[4] = { 0,-1,0,1 };
	const int dc[4] = { 1,0,-1,0 };
	const int inv[4] = { 1,2,3,0 };
	const int checkR[4] = { 0,0,1,1 };
	const int checkC[4] = { 0,1,0,1 };
	cod dragon[20];
	int direct[20][1024];
	int sede[20];
	int n;

	int getSagack()
	{
		for (int i = 0; i < n; i++)
		{
			makeDragon(i, sede[i]);
		}

		int res = 0;
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				int cnt = 0;
				for (int d = 0; d < 4; d++)
				{
					cnt += map[i + checkR[d]][j + checkC[d]];
				}
				res += cnt >> 2;
			}
		}
		return res;
	}

	void makeDragon(int nD, int sede)
	{
		int nowLength = 1;
		for (int i = 0; i < sede; i++)
		{
			for (int j = nowLength - 1; j >= 0; j--)
			{
				int dir = inv[direct[nD][j]];
				direct[nD][nowLength++] = dir;
				dragon[nD].r += dr[dir];
				dragon[nD].c += dc[dir];

				map[dragon[nD].r][dragon[nD].c] = 1;
			}
		}
	}



	void init()
	{
		cin >> n;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < n; i++)
		{
			cin >> dragon[i].c >> dragon[i].r >> direct[i][0] >> sede[i];
			map[dragon[i].r][dragon[i].c] = 1;

			dragon[i].r += dr[direct[i][0]];
			dragon[i].c += dc[direct[i][0]];

			map[dragon[i].r][dragon[i].c] = 1;
		}

	}
}DragonInfo;

int DragonCurve()
{
	DragonInfo.init();
	int res = DragonInfo.getSagack();
	cout << res << '\n';
	return 0;
}