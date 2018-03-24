#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>

using namespace std;

char JJARO_MAP[10][10];

struct JJARO_COD
{
	char tag;
	int x;
	int y;
	int count;

	JJARO_COD& operator=(const JJARO_COD& in)
	{
		tag = in.tag;
		x = in.x;
		y = in.y;
		count = in.count;
		return *this;
	}
};

const int JJARO_UP = 0;
const int JJARO_RIGHT = 1;
const int JJARO_DOWN = 2;
const int JJARO_LEFT = 3;

int JJARO_dx[4] = { 0,1,0,-1 };
int JJARO_dy[4] = { -1,0,1,0 };

bool JJaroCanMove(int x, int y, int d)
{
	return JJARO_MAP[y + JJARO_dy[d]][x + JJARO_dx[d]] != '#';
}

bool JJaroGoal(int x, int y)
{
	return JJARO_MAP[y][x] == 'O';
}

int JJARO_move(queue<JJARO_COD> &red_cods, queue<JJARO_COD> &blue_cods)
{
	int result = 0;
	JJARO_COD blue, red;
	bool End = false;
	while (!red_cods.empty() && result <= 10&& !End)
	{
		blue = blue_cods.front();
		red = red_cods.front();
		blue_cods.pop(); red_cods.pop();
		JJARO_COD first, second;
		queue<JJARO_COD> *first_que, *second_que;
		bool move = false;
		for (int d = 0; d < 4; d++)
		{
			if (!JJaroCanMove(red.x, red.y, d) && !JJaroCanMove(blue.x, blue.y, d)) continue;
			
			switch (d)
			{
			case JJARO_UP:
				first = red.y < blue.y ? red : blue;
				second = red.y >= blue.y ? red : blue;

				first_que = red.y < blue.y ? &red_cods: &blue_cods;
				second_que = red.y >= blue.y ? &red_cods : &blue_cods;
				break;
			case JJARO_DOWN:
				first = red.y > blue.y ? red : blue;
				second = red.y <= blue.y ? red : blue;
				
				first_que = red.y > blue.y ? &red_cods : &blue_cods;
				second_que = red.y <= blue.y ? &red_cods : &blue_cods;
				break;
			case JJARO_RIGHT:
				first = red.x > blue.x ? red : blue;
				second = red.x <= blue.x ? red : blue;
				first_que = red.x > blue.x ? &red_cods : &blue_cods;
				second_que = red.x <= blue.x ? &red_cods : &blue_cods;
				break;

			case JJARO_LEFT:
				first = red.x < blue.x ? red : blue;
				second = red.x >= blue.x ? red : blue;

				first_que = red.x < blue.x ? &red_cods : &blue_cods;
				second_que = red.x >= blue.x ? &red_cods : &blue_cods;
				break;
			}
			bool isContinue = false;
			//set balls position
			if (JJaroCanMove(first.x, first.y, d))
			{
				while (JJARO_MAP[first.y+ JJARO_dy[d]][first.x + JJARO_dx[d]] != '#')
				{
					move = true;
					first.y += JJARO_dy[d];
					first.x += JJARO_dx[d];
					End = JJARO_MAP[first.y][first.x] == 'O' && first.tag == 'R';
					isContinue = JJARO_MAP[first.y][first.x] == 'O' && first.tag == 'B';
					if (isContinue || End) break;
				}
				isContinue |= JJARO_MAP[first.y][first.x] == 'O' && first.tag == 'B';
			}
			JJARO_MAP[first.y][first.x] = !End && !isContinue ? 'B' : 'O';

			if (JJaroCanMove(second.x, second.y, d))
			{
				while (JJARO_MAP[second.y+ JJARO_dy[d]][second.x+JJARO_dx[d]] != '#')
				{
					if (JJARO_MAP[second.y + JJARO_dy[d]][second.x + JJARO_dx[d]] == 'B') break;
					move = true;
					second.y += JJARO_dy[d];
					second.x += JJARO_dx[d];
					End |= JJARO_MAP[second.y][second.x] == 'O' && second.tag == 'R';
					isContinue |= JJARO_MAP[second.y][second.x] == 'O' && second.tag == 'B';
					if (isContinue) break;
				}
				isContinue |= JJARO_MAP[second.y][second.x] == 'O' && second.tag == 'B';
			}

			first.count++; second.count++;
			result = first.count;
			JJARO_MAP[first.y][first.x] = JJARO_MAP[first.y][first.x] == 'B' ? '.' : JJARO_MAP[first.y][first.x];
			if (isContinue)
			{
				End = false;
				continue;
			}
			if (End) break;
			if (!move) continue;
			first_que->push(first);
			second_que->push(second);
		}
	}
	if (!End) return 100;
	return result;
}


void Jjarro()
{
	int N, M;
	cin >> N >> M;
	
	memset(JJARO_MAP, 0, sizeof(JJARO_MAP));
	JJARO_COD red, blue;
	queue<JJARO_COD> red_cods,blue_cods;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> JJARO_MAP[i][j];
			if (JJARO_MAP[i][j] == 'R')
			{
				red.tag = 'R';
				red.x = j;
				red.y = i;
				JJARO_MAP[i][j] = '.';
				red.count = 0;
				red_cods.push(red);
			}
			else if (JJARO_MAP[i][j] == 'B')
			{
				blue.tag = 'B';
				blue.x = j; blue.y = i; blue.count = 0;
				blue_cods.push(blue);
				JJARO_MAP[i][j] = '.';				
			}
		}
	}

	int result = JJARO_move(red_cods, blue_cods);
	cout << (result > 10 ? -1 : result) << endl;
}