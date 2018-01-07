#pragma once
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

char PopPing_map[300][300];
//left-up,up,right-up, right,right-down, down,left-down ,left
const int PoPing_dx[8] = { -1,0,1,1,1,0,-1,-1 };
const int PoPing_dy[8] = { -1,-1,-1,0,1,1,1 ,0 };

bool IsWall(int x, int y, int size)
{
	return x < 0 || x >= size || y < 0 || y >= size;
}

void SetMap(int x, int y, int size)
{

	for (int i = 0; i < 8; i++)
	{
		if (!IsWall(x + PoPing_dx[i], y + PoPing_dy[i], size))
		{
			PopPing_map[y + PoPing_dy[i]][x + PoPing_dx[i]] = PopPing_map[y + PoPing_dy[i]][x + PoPing_dx[i]] == '*' ? '*' : ++PopPing_map[y + PoPing_dy[i]][x + PoPing_dx[i]];
		}
	}
}

void ClickZero(int x, int y, int size)
{
	queue<pair<int, int> > que;

	PopPing_map[y][x] = '*';
	que.push({ x,y });
	pair<int, int> now;
	while (!que.empty())
	{
		now = que.front();
		que.pop();
		x = now.first;
		y = now.second;

		for (int d = 0; d < 8; d++)
		{
			if (!IsWall(x+ PoPing_dx[d], y+ PoPing_dy[d], size))
			{
				if (PopPing_map[y + PoPing_dy[d]][x + PoPing_dx[d]] == '*') continue;
				if (PopPing_map[y + PoPing_dy[d]][x + PoPing_dx[d]] == 0) que.push({ x + PoPing_dx[d], y + PoPing_dy[d] });
				PopPing_map[y + PoPing_dy[d]][x + PoPing_dx[d]] = '*';
			}
		}
	}
}

void PopPing()
{

	typedef pair<int, int> PII;
	int T,N;
	cin >> T;

	for (int k = 1; k <= T; k++)
	{
		cin >> N;
		int result = 0;
		char input;
		queue<PII> que;
		PII now = { 0,0 };
		memset(PopPing_map, 0, sizeof(PopPing_map));

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >>input;
				if (input == '*')
				{
					PopPing_map[i][j] = '*';
					SetMap(j, i, N);
				}
			}
		}

		//for (int i = 0; i < N; i++)
		//{
		//	for (int j = 0; j < N; j++)
		//		cout << (int)PopPing_map[i][j] << " ";
		//	cout << endl;
		//}

		//click zeros
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (PopPing_map[i][j] != 0)continue;

				else
				{
					ClickZero(j, i, N);
					result++;
				}
			}
		}

		//click else
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)

			{
				if (PopPing_map[i][j] != '*') result++;
			}
		}
		


		cout << "#" << k << " " << result << endl;
	}
}