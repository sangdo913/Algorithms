#pragma once
#include<iostream>
#include<cstdio>
using namespace std;
int Queen_num;
int Queen_MAP[10][10];

void Queen_Set(int set_num, int length_max, int x, int y)
{
	//down
	for (int row = y + 1; row < length_max; row++)
	{
		Queen_MAP[row][x] += set_num;
	}
	//right down
	for (int row = y + 1,  col = x + 1; row < length_max && col < length_max; row++, col++)
	{
		Queen_MAP[row][col] += set_num;
	}
	//left down
	for (int row = y + 1,col = x - 1; row < length_max && col >= 0; row++, col--)
	{
		Queen_MAP[row][col] += set_num;
	}
}

void Queen_GetQueen(int length, int length_max)
{
	if (length_max == length)
	{
		Queen_num++;
		return;
	}

	for (int i = 0; i < length_max; i++)
	{
		if (Queen_MAP[length][i] == 0)
		{
			Queen_Set(-1, length_max, i, length);
			Queen_GetQueen(length + 1, length_max);
			Queen_Set(1, length_max, i,length);
		}
	}


	return;
}

void N_Queens()
{
	int T, N;

	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N;j++)
			Queen_MAP[i][j] = 0;
		}

		Queen_num = 0;
		Queen_GetQueen(0,N);

		printf("#%d %d\n", tc,Queen_num);
	}
}