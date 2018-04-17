#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

struct CCTVInfo
{
	typedef struct Cod { int r, c; } cod;
	typedef enum {UP = 0b1, RIGHT = 0b0010, DOWN = 0b0100, LEFT = 0b1000} DIR;
	typedef enum {floor = 0, wall = 6, sensing = 7, final = -1} OBSTACLE;
	typedef enum {U = 0, R, D, L} CONV;

	const int CCTVCount[6] = { -1,4,2,4,4,1 };
	const int CCTVDirect[6] = { -1,RIGHT, LEFT | RIGHT, UP | RIGHT, LEFT | UP | RIGHT, 0b1111};
	const int dr[4] = { -1,0,1,0 };
	const int dc[4] = { 0,1,0,-1 };
	int conv[4];

	cod camera[8];

	int map[10][10];
	int n, m;
	int cNum, minArea;
	int check[10][10];
	int checkFloor()
	{
		int res = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				res += (map[i][j] == floor);
			}
		}
		return res;
	}


	void sense(cod &pos, int direct, int cnt)
	{
		cod next;
		next.r = pos.r + dr[direct];
		next.c = pos.c + dc[direct];

		while (map[next.r][next.c] != wall && map[next.r][next.c] != final)
		{
			if (check[next.r][next.c] == -1 && map[next.r][next.c] == floor)
			{
				map[next.r][next.c] = sensing;
				check[next.r][next.c] = cnt;
			}
			next.r += dr[direct];
			next.c += dc[direct];
		}
	}

	void cancleSensing(cod &pos, int direct, int cnt)
	{
		cod next;

		next.r = pos.r + dr[direct];
		next.c = pos.c + dc[direct];
		while (map[next.r][next.c] != wall && map[next.r][next.c] != final)
		{
			if (map[next.r][next.c] == sensing && check[next.r][next.c] == cnt)
			{
				map[next.r][next.c] = 0;
				check[next.r][next.c] = -1;
			}

			next.r += dr[direct];
			next.c += dc[direct];
		}
	}

	int min(int i1, int i2)
	{
		return i1 < i2 ? i1 : i2;
	}


	void getSafeArea(int cnt)
	{
		if (cnt == cNum)
		{
			minArea = min(minArea, checkFloor());
			return;
		}

		for (int d = 0; d < CCTVCount[map[camera[cnt].r][camera[cnt].c]]; d++)
		{
			int directions = CCTVDirect[map[camera[cnt].r][camera[cnt].c]];

			for (int i = 0; i < 4; i++)
			{
				if (directions & conv[i])
				{
					sense(camera[cnt], (i + d) % 4,cnt );
				}
			}

			getSafeArea(cnt + 1);

			for (int i = 0; i < 4; i++)
			{
				if (directions & conv[i])
				{
					cancleSensing(camera[cnt], (i + d) % 4,cnt);
				}
			}
		}
	}

	void init()
	{
		memset(map, -1, sizeof(map));
		memset(check, -1, sizeof(check));

		cNum = 0;
		conv[U] = UP;
		conv[R] = RIGHT;
		conv[D] = DOWN;
		conv[L] = LEFT;
		minArea = 100;

		scanf("%d %d\n", &n, &m);
		for(int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			{
				scanf("%d ", &map[i][j]);
				if (map[i][j] != wall && map[i][j] != floor)
				{
					camera[cNum].r = i;
					camera[cNum++].c = j;
				}
			}
	}
}CCTV_info;

int CCTV()
{
	CCTV_info.init();
	CCTV_info.getSafeArea(0);

	int res = CCTV_info.minArea;

	cout << res << '\n';

	return 0;
}