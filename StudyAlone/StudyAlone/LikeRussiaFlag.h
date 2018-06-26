#pragma once
#include<cstdio>
#include<cstring>

char colors[51][51];
int nums[51][4] = { 0 }, n, m;
enum COLOR {WH = 1, BL = 2, RE = 3};

int conv[4];

int memoi[51][51][51] = { 0 };

int LikeRussiaFlag()
{
	int t;
	scanf("%d\n", &t);
	conv[WH] = 'W';
	conv[RE] = 'R';
	conv[BL] = 'B';

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d\n", &n, &m);
		memset(memoi, 0, sizeof(memoi));

		for (int i = 1; i <= n; i++)
		{
			scanf("%s\n", colors[i]);

			for(int j = 1; j < 4; j++)
				nums[i][j] = nums[i - 1][j];

			for (int j = 0; j < m; j++)
			{
				nums[i][WH] += colors[i][j] != conv[WH];
				nums[i][RE] += colors[i][j] != conv[RE];
				nums[i][BL] += colors[i][j] != conv[BL];
			}
		}

		int min = 98764321;

		for (int st = 2; st <= n - 1; st++)
		{
			for (int ed = st; ed <= n - 1; ed++)
			{
				int cnt = nums[st - 1][WH] - nums[0][WH];
				cnt += nums[ed][BL] - nums[st - 1][BL];
				cnt += nums[n][RE] - nums[ed][RE];

				min = min < cnt ? min : cnt;
			}
		}

		printf("#%d %d\n", tc, min);
	}
	return 0;
}
