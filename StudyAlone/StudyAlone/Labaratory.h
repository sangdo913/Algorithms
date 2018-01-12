#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
// labaratory https://www.acmicpc.net/problem/14502
using namespace std;
int LAB_MAP[10][10];

int LAB_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

// get the value of num of safty-areas when they are full
int LabGetZeros( int N, int M)
{
	int map[10][10];
	typedef pair<int, int> II;
	queue<II> que;
	const int dx[4] = { 0,1,0,-1 };
	const int dy[4] = { -1,0,1,0 };

	memcpy(map, LAB_MAP, sizeof(map));
	int result = 0;
	for (int i = 1; i <= N; i++)
	{
		//store first cod of virus
		for (int j = 1; j <= M; j++)
		{
			if (map[i][j] == 2) que.push({ j,i });
		}
	}
	//fill virus in map
	while (!que.empty())
	{
		II cod = que.front();
		que.pop();
		int x, y;
		for (int d = 0; d < 4; d++)
		{
			x = cod.first + dx[d];			y = cod.second + dy[d];
			if (map[y][x] != 0) continue; // not floor
			que.push({ x,y });
			map[y][x] = 2;
		}
	}

	// get the value of safty areas
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (map[i][j] == 0) result++;
		}
	}
	return result;
}

int LabGetMAX(int x, int y,int sizeX, int sizeY, int num_wall)
{
	//if number of num_wall is 3, then get the number of safy areas!
	if (num_wall == 3)
	{
		return LabGetZeros(sizeY,sizeX);
	}

	int ret = -1;
	for (int i = y; i <= sizeY; i++)
	{
		int j = i == y ? x : 1;
		for (; j <= sizeX; j++)
		{
			if (LAB_MAP[i][j] != 0) continue;
			LAB_MAP[i][j] = 1; // construct wall
			ret = LAB_MAX(ret,LabGetMAX(j, i, sizeX, sizeY, num_wall + 1)); // get max value of safty areas
			LAB_MAP[i][j] = 0; //destruct wall
		}
	}

	// return max
	return ret;
}

void Labaratory()
{
	int N, M;
	cin >> N >> M;
	//store number of 0;
	int result;
	memset(LAB_MAP, -1, sizeof(LAB_MAP));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> LAB_MAP[i][j];
		}
	}
	result = LabGetMAX(0,0,M,N,0);
	cout << result << endl;
}