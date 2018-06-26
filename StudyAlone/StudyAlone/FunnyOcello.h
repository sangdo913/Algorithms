#pragma once
#include<cstdio>
#include<cstring>

int n, m;
int map[10][10];
enum COLOR {WH = 2, BL = 1};
int nums[3];

int dy[8] = { -1,-1,-1, 0, 0, 1,1,1 };
int dx[8] = { -1, 0, 1,-1, 1,-1,0,1 };

int Q[100][2];
int fr = 0 , re = 0;

int getNum(int x, int y, int col)
{
	int ret = 0;

	for (int d = 0; d < 8; d++)
	{
		int n = 0;
		int nX = x + dx[d];
		int nY = y + dy[d];

		fr = re = 0;

		while (map[nY][nX] != col)
		{
			if (map[nY][nX] == 0) break;
			else if (map[nY][nX] == -1) break;
			n++;
			Q[re][0] = nY;
			Q[re++][1] = nX;
			
			nX += dx[d];
			nY += dy[d];
		}

		if (map[nY][nX] == col)
		{
			while (re != fr)
			{
				map[Q[fr][0]][Q[fr][1]] = col;
				fr++;
			}
			ret += n;
		}
	}

	return ret;
}

int FunnyOcello()
{
	int t;
	scanf("%d\n", &t);

	memset(map, -1, sizeof(map));

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d\n", &n, &m);

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				map[i][j] = 0;
		}

		int x, y, col;

		y = x = n / 2;

		map[y][x] = WH;
		map[y + 1][x] = BL;
		map[y + 1][x + 1] = WH;
		map[y][x + 1] = BL;
		nums[1] = nums[2] = 2;

		while (m--)
		{
			scanf("%d %d %d\n", &y, &x, &col);
			int num = getNum(x, y, col);

			map[y][x] = col;

			nums[col] += num + 1;
			nums[col ^ 3] -= num;
		}

		printf("#%d %d %d\n", tc, nums[BL], nums[WH]);
	}
	return 0;
}