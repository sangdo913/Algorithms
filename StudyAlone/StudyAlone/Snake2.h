#pragma once
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<deque>

const int SNAKE2_DIR = 1;
const int SNAKE2_TIME = 0;
char SNAKE2_MAP[102][102];
int SNAKE2_CHANGE[2][101];

using namespace std;
struct SNAKE2_COD
{
	int x;
	int y;
};
void Snake2()
{
	int N, K, L;

	cin >> N;
	memset(SNAKE2_MAP, -1, sizeof(SNAKE2_MAP));
	fill(SNAKE2_CHANGE[0], SNAKE2_CHANGE[0] + 101, 10000);
	//make wall
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			SNAKE2_MAP[i][j] = 0;
		}
	}
	cin >> K;
	int x, y;
	for (int i = 0; i < K; i++)
	{
		cin >> y >> x;
		SNAKE2_MAP[y][x] = 2;
	}

	cin >> L;
	char direct;
	for (int i = 0; i < L; i++)
	{
		cin >> x >> direct;
		SNAKE2_CHANGE[0][i] = x;
		SNAKE2_CHANGE[1][i] = direct;
	}
	int time_count = 0;
	int change_count = 0;
	const int UP = 0;
	const int RIGHT = 1;
	const int DOWN = 2;
	const int LEFT = 3;
	direct = RIGHT;
	bool isAlive = true;
	x = 1;
	y = 1;
	SNAKE2_MAP[y][x] = 1;

	// up right  down left
	const int dx[4] = { 0,1,0,-1 };
	const int dy[4] = { -1,0,1,0 };
	deque<SNAKE2_COD> snake_info;
	snake_info.push_front({ x,y });
	while (isAlive)
	{
		time_count++;
		x += dx[direct];
		y += dy[direct];

		//change direct
		if (SNAKE2_CHANGE[SNAKE2_TIME][change_count] == time_count)
		{
			switch (SNAKE2_CHANGE[SNAKE2_DIR][change_count])
			{
			case'D':
				direct = (++direct) % 4;
				break;
			case'L':
				direct = (direct + 3) % 4;
				break;
			default:
				break;
			}
			change_count++;
		}
		if (abs(SNAKE2_MAP[y][x]) == 1)
		{
			isAlive = false;
			break;
		}


		// reset head and tail
		// record to map about head and tail changed
		snake_info.push_front({ x,y});
		if (SNAKE2_MAP[y][x] == 0)
		{
			SNAKE2_COD tail = snake_info.back();
			SNAKE2_MAP[tail.y][tail.x] = 0;
			snake_info.pop_back();
		}
		SNAKE2_MAP[y][x] = 1;
	}

	cout << time_count << endl;
}