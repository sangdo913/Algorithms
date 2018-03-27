#pragma once
#include<iostream>
#include<string.h>
using namespace std;

struct BlockMeSang_Mesang
{
	int sum;
	int x;
	int y;
	int direct;
};

bool BlockMeSang_Bound(int x, int y,int n)
{
	return (x == 0) || (y == 0) || (x == n - 1) || (y == n - 1);
}

int BlockMeSang()
{
	typedef BlockMeSang_Mesang mesang;
	const int dx[5] = { 0,0,0,-1,1 };
	const int dy[5] = { 0,-1,1,0,0 };
	const int nextD[5] = { 0,2,1,4,3 };

	//그 칸에 있는 미생물의 수
	int nextSum[100][100];
	//그 칸의 기준이 되는 미생물 번호
	int nextStd[100][100];

	mesang infos[1000];
	int t,n,k,m;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < k; i++)
		{
			scanf("%d %d %d %d", &infos[i].y, &(infos[i].x), &infos[i].sum, &infos[i].direct);
		}

		//시간 체크
		while (m--)
		{
			memset(nextSum, 0, sizeof(nextSum));
			memset(nextStd, -1, sizeof(nextStd));

			//미생물들 이동
			for (int i = 0; i < k; i++)
			{
				if (infos[i].sum == 0) continue;

				infos[i].x += dx[infos[i].direct];
				infos[i].y += dy[infos[i].direct];

				//벽에 닿음
				if (BlockMeSang_Bound(infos[i].x, infos[i].y, n))
				{
					infos[i].direct = nextD[infos[i].direct];
					infos[i].sum /= 2;
				}

				//안닿음
				else
				{
					//기준
					int min = nextStd[infos[i].y][infos[i].x];

					//1. 기준이 안정해졌으면 미생물 셀 번호를 그대로넣는다.
					//2. 기준보다 많으면 기준을 최신화하고 기준에 있던 미생물을 0으로 만든다.
					//3. 기준보다 수가 적으면 적은 수의 미생물을 0으로 만든다.
					nextSum[infos[i].y][infos[i].x] += infos[i].sum;

					if (min == -1)
					{
						nextStd[infos[i].y][infos[i].x] = i;
					}
					else if ((infos[min].sum < infos[i].sum))
					{
						infos[min].sum = 0;
						nextStd[infos[i].y][infos[i].x] = i;
					}
					else
					{
						infos[i].sum = 0;
					}
				}
			}

			// 미생물수를 최신화한다.
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if(nextStd[i][j] != -1) infos[nextStd[i][j]].sum = nextSum[i][j];
		}

		int res = 0;

		for (int i = 0; i < k; i++)
		{
			res += infos[i].sum;
		}
		printf("#%d %d\n", tc, res);
	}
	return 0;
}