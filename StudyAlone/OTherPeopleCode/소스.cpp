#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int map[50][50];
const int dr[4] = { -1,1,0,0 };

int n, m;
const int dc[4] = { 0,0,-1,1 };
const int change[4][4] = { { 2,1,3,0 },{ 0,2,1,3 },{ 3,0,2,1 },{ 1,3,0,1 } };
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
struct Cleaner
{
	int direct;
	int r, c;
	int clean;
	int check()
	{
		int nextR = r + dr[change[direct][0]];
		int nextC = c + dc[change[direct][0]];

		bool dirty = false;

		for (int i = 0; i < 4; i++)
		{
			nextR = r + dr[i];
			nextC = c + dc[i];

			dirty |= map[nextR][nextC] == 0;
		}

		if (!dirty)
		{
			nextR = r + dr[change[direct][1]];
			nextC = c + dc[change[direct][1]];
			if (map[nextR][nextC] == 1) return -1;
			r = nextR; c = nextC;
			return 2;
		}

		nextR = r + dr[change[direct][0]];
		nextC = c + dc[change[direct][0]];

		if (map[nextR][nextC] == 0)
		{
			r = nextR;
			c = nextC;
			direct = (direct + 3) % 4;
			return 1;
		}

		direct = (direct + 3) % 4;
		return 2;
	}
	int process()
	{
		while (true)
		{
			if (map[r][c] == 0)
			{
				map[r][c] = 2;
				clean++;
			}


			while (true)
			{
				int flag = check();
				if (flag == 1) break;
				if (flag == -1) return clean;

			}
		}
	}
} cleaner;
int main()
{
	scanf("%d %d\n", &n, &m);
	scanf("%d %d %d\n", &cleaner.r, &cleaner.c, &cleaner.direct);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%d", &map[i][j]);
	}

	int res = cleaner.process();
	printf("%d\n", res);
	return 0;
}