#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<stack>
#include<queue>
#include<cstdio>
using namespace std;

char info[1000][1000];

// left up, up, right up, left, right, left down, down, right down
const int dx[8] = { -1,0,1,-1,1,-1,0,1 };
const int dy[8] = { -1,-1,-1,0,0,1,1,1 };

typedef struct SandPosition
{
	int first;
	int second;
}PII;

bool SandTopValidArray(int x, int y, int h,int w)
{
	return !(x < 0 || x >= w || y < 0 || y >= h);
}

void SandGetValue(queue<PII> &que ,int h,int w)
{
	int count = que.size();

	for (int ct = 0; ct < count; ct++)
	{
		int x = que.front().first;
		int y = que.front().second;
		que.pop();
		info[y][x] = '.';

		for (int i = 0; i < 8; i++)
		{
			if (!SandTopValidArray(x + dx[i], y + dy[i], h, w)) continue;
			if (info[y + dy[i]][x + dx[i]] <= '0' || info[y + dy[i]][x + dx[i]] >= '9') continue;

			info[y + dy[i]][x + dx[i]]--;

			if (info[y+dy[i]][x+dx[i]] != '0') continue;
			que.push({ x + dx[i], y + dy[i] });
		}
	}
}

void SandTop()
{
	int H, W, K;
	int result;

	cin >> K;

	for (int k = 1; k <= K; k++)
	{
		queue<PII> next;
		memset(info, 0, sizeof(info));
		cin >> H >> W;
		result = 0;

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				cin >> info[i][j];
			}
		}

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if(info[i][j] == '.')
					for (int k = 0; k < 8; k++)
					{
						if (!SandTopValidArray(j + dx[k], i + dy[k], H, W)) continue;
						if (info[i + dy[k]][j + dx[k]] >= '9' || info[i+dy[k]][j+dx[k]] <= '0') continue;

						info[i + dy[k]][j + dx[k]] --;

						if (info[i + dy[k]][j + dx[k]] != '0') continue;
						next.push({ j + dx[k],i + dy[k] });
					}
			}
		}
	
		while(!next.empty())
		{
			SandGetValue(next,H,W);			
			result = ++result;
		}

		printf("#%d %d\n", k, result);
	}
}