//#pragma once
//#include<iostream>
//#include<cstdio>
//using namespace std;
//int Queen_num;
//int Queen_MAP[10][10];
//
//void Queen_Set(int set_num, int length_max, int x, int y)
//{
//	down
//	for (int row = y + 1; row < length_max; row++)
//	{
//		Queen_MAP[row][x] += set_num;
//	}
//	right down
//	for (int row = y + 1,  col = x + 1; row < length_max && col < length_max; row++, col++)
//	{
//		Queen_MAP[row][col] += set_num;
//	}
//	left down
//	for (int row = y + 1,col = x - 1; row < length_max && col >= 0; row++, col--)
//	{
//		Queen_MAP[row][col] += set_num;
//	}
//}
//
//void Queen_GetQueen(int length, int length_max)
//{
//	if (length_max == length)
//	{
//		Queen_num++;
//		return;
//	}
//
//	for (int i = 0; i < length_max; i++)
//	{
//		if (Queen_MAP[length][i] == 0)
//		{
//			Queen_Set(-1, length_max, i, length);
//			Queen_GetQueen(length + 1, length_max);
//			Queen_Set(1, length_max, i,length);
//		}
//	}
//
//
//	return;
//}
//
//void N_Queens()
//{
//	int T, N;
//
//	scanf("%d", &T);
//
//	for (int tc = 1; tc <= T; tc++)
//	{
//		scanf("%d", &N);
//		for (int i = 0; i < N; i++)
//		{
//			for (int j = 0; j < N;j++)
//			Queen_MAP[i][j] = 0;
//		}
//
//		Queen_num = 0;
//		Queen_GetQueen(0,N);
//
//		printf("#%d %d\n", tc,Queen_num);
//	}
//}

#include<cstdio>

int n, map[12][12];

int dx[3] = { -1,0,1 };

int nQueen(int depth)
{
	int res = 0;

	if (depth == n)
	{
		for (int i = 1; i <= n; i++)
		{
			res += map[depth][i] == 0;
		}
		return res;
	}


	for (int i = 1; i <= n; i++)
	{
		if (map[depth][i] == 0)
		{
			int cnt = 1;
			for (int j = depth + 1; j <= n; j++)
			{
				if (i - cnt > 0) map[j][i - cnt]++;
				if (i + cnt <= n) map[j][i + cnt]++;
				map[j][i]++;
				cnt++;
			}

			res += nQueen(depth + 1);

			cnt = 1;
			for (int j = depth + 1; j <= n; j++)
			{
				if (i - cnt > 0) map[j][i - cnt]--;
				if (i + cnt <= n) map[j][i + cnt]--;
				map[j][i]--;
				cnt++;
			}
		}
	}

	return res;
}

int NQueen()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d\n", &n);
		int res = nQueen(1);
		printf("#%d %d\n", tc, res);
	}
	return 0;
}