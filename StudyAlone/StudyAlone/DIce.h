#pragma once
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iomanip>
using namespace std;
const int DICE_UP = 0;
const int DICE_NORTH = 1;
const int DICE_EAST = 2;
const int DICE_WEST = 3;
const int DICE_SOUTH = 4;
const int DICE_DOWN = 5;


int DICE_dx[5] = { 0,1,-1,0,0 };
int DICE_dy[5] = { 0,0,0,-1,1 };
const int DICE_N = 3;
const int DICE_E = 1;
const int DICE_W = 2;
const int DICE_S = 4;
struct DICE_COD
{
	int x;
	int y;

};
int UNDS[4] = { DICE_UP,DICE_NORTH,DICE_DOWN,DICE_SOUTH };
int URDW[4] = { DICE_UP,DICE_EAST,DICE_DOWN,DICE_WEST };

int DICE_MAP[22][22];
struct DICE_DICE
{
	int numbers[6];
	DICE_COD now;
	DICE_DICE(DICE_COD now) : now(now)
	{
		memset(numbers, 0, sizeof(numbers));
	}

	int GetNumber()
	{
		return numbers[DICE_UP];
	}

	void SetNumber()
	{
		if (DICE_MAP[now.y][now.x] == 0)
		{
			DICE_MAP[now.y][now.x] = numbers[DICE_DOWN];
		}
		else
		{
			numbers[DICE_DOWN] = DICE_MAP[now.y][now.x];
			DICE_MAP[now.y][now.x] = 0;
		}
	}

	bool MOVE(int dir)
	{
		if (DICE_MAP[now.y + DICE_dy[dir]][now.x + DICE_dx[dir]] == -1)
		{
			return false;
		}

		now.x += DICE_dx[dir];
		now.y += DICE_dy[dir];
		int	temp = numbers[UNDS[DICE_UP]];
		int index = 0;
		int rotate = dir == DICE_N || dir == DICE_E ? -1 : 1;
		int* rotateArr = dir == DICE_N || dir == DICE_S ? UNDS : URDW;

		for (int i = 0; i < 3; i++)
		{
			numbers[rotateArr[index]] = numbers[rotateArr[(index + 4 + rotate) % 4]];
			index = (index + 4 + rotate) % 4;
		}
		numbers[rotateArr[index]] = temp;

		SetNumber();
		return true;
	}
};
void Dice()
{
	int K, N, M, x, y;
	cin >> N >> M >> y >> x >> K;
	DICE_DICE dice({ ++x,++y });

	memset(DICE_MAP, -1, sizeof(DICE_MAP));
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> x;
			DICE_MAP[i][j] = x;
		}
	}
	
	for (int com = 0; com < K; com++)
	{
		cin >> x;
		if (dice.MOVE(x))cout << dice.GetNumber() << endl;
	}
}