#pragma once
#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
using namespace std;

int MAP2048[22][22];
int max_2048 = -1;
bool ADDED2048[22][22];
const int dx_2048[4] = { 0,1,0,-1 };
const int dy_2048[4] = { -1,0,1,0 };

void GetMax(int map[22][22], int count, int d, int size)
{

	if (count == 6) return;
	int temp_map[22][22];
	static const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, INIT = 4;
	memset(ADDED2048, false, sizeof(ADDED2048));
	memcpy(temp_map, map, sizeof(MAP2048));

	int rs = d == UP || d== LEFT ? 1 : size;
	int cs = d == RIGHT || d == DOWN? size : 1;
	int flag = d == RIGHT || d == DOWN ? -1 : 1;
	int dx, dy;

	if(d!= 4)
	for (int r = rs; temp_map[r][1] != -1; r += flag)
	{
		for (int c = cs; temp_map[r][c] != -1; c += flag)
		{
			if (temp_map[r][c] == 0) continue;
			dx = c; dy = r;

			//0이 아닌 바닥 좌표를 찾아줌
			do
			{
				dx += dx_2048[d]; dy += dy_2048[d];
			} while (temp_map[dy][dx] == 0);

			//같은 경우 더해주고 맥스값 갱신
			if (temp_map[dy][dx] == temp_map[r][c] && !ADDED2048[dy][dx])
			{
				temp_map[dy][dx] += temp_map[r][c];
				temp_map[r][c] = 0;
				ADDED2048[dy][dx] = true;
				max_2048 = max(temp_map[dy][dx], max_2048);
			}
			//바닥인 경우 이동
			else
			{
				if (dy - dy_2048[d] == r && dx - dx_2048[d] == c) continue;
				temp_map[dy-dy_2048[d]][dx-dx_2048[d]] = temp_map[r][c];
				temp_map[r][c] = 0;
			}
		}
	}
	count++;
	for (int i = 0; i < 4; i++)
	{
		GetMax(temp_map,count, i,size);
	}

}


void Solve2048()
{
	int N;
	cin >> N;
	memset(MAP2048, -1, sizeof(MAP2048));

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAP2048[i][j];
			max_2048 = max(MAP2048[i][j], max_2048);
		}
	}
	GetMax(MAP2048, 0, 4, N);
	cout << max_2048 << endl;
}