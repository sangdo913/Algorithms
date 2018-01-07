#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

struct SNAKE_POS
{
	long long x;
	long long y;

	SNAKE_POS& operator=(const SNAKE_POS &d)
	{
		x = d.x;
		y = d.y;
		return *this;
	}
};

long long SNAKE_MIN(long long x1, long long x2)
{
	return x1 > x2 ? x2 : x1;
}
long long SNAKE_ABS(long long x)
{
	return x > 0 ? x : -1 * x;
}

struct SNAKE_LINE
{
	SNAKE_POS start;
	SNAKE_POS end;
	char type;
	
	long long GetLength(SNAKE_POS p)
	{
		long long min = INT64_MAX;
		switch (type)
		{
		case 'R':
			if (start.x != p.x) return SNAKE_ABS(start.x - p.x);
			else return SNAKE_MIN(SNAKE_ABS(start.y - p.y), SNAKE_ABS(end.y - p.y));
			break;
		case 'C':
			if (start.y != p.y) return SNAKE_ABS(start.y - p.y);
			else return SNAKE_MIN(SNAKE_ABS(start.x - p.x), SNAKE_ABS(end.x - p.x));
			break;

		}
	}

	long long GetLength()
	{
		return type == 'C' ? SNAKE_ABS(start.x - end.x) : SNAKE_ABS(start.y - end.y);
	}


	bool IsCross(SNAKE_LINE d1)
	{
		bool result;
		if (d1.type == type)
		{
			switch (type)
			{
			case 'R':
				if (start.x != d1.start.x) return false;
				else
				{
					result = false;
					result |= (start.y <= d1.end.y) && (start.y >= d1.start.y);
					result |= (end.y <= d1.end.y) && (start.y >= d1.start.y);
					result |= start.y <= d1.start.y && end.y >= d1.end.y;
				}
				break;
			case'C':
				if (start.y != d1.start.y) return false;
				else
				{
					result = false;
					result |= (start.x <= d1.end.x) && (start.x >= d1.start.x );
					result |= (end.x <= d1.end.x) && (end.x >= d1.start.x);
					result |= start.x <= d1.start.x && end.x >= d1.end.x;
				}
				break;
			}
		}

		else
		{
			long long x = type == 'C' ? d1.start.x : start.x;
			long long y = type == 'C' ? start.y : d1.start.y;
			SNAKE_LINE R = type == 'R' ? *this : d1;
			SNAKE_LINE C = type == 'C' ? *this : d1;
			result = true;
			result &= x <= C.end.x && x >= C.start.x;
			result &= y <= R.end.y && y >= R.start.y;
		}

		return result;
	}
};

void Snake()
{
	const int UP = 0;
	const int RIGHT = 1;
	const int DOWN = 2;
	const int LEFT = 3;
	long long L,length = 0;
	int R_count;
	long long times[1001];
	char rotate[1001];
	//up right down left (direct : clock wise)
	long long dx[4] = { 0,1,0,-1 };
	long long dy[4] = { 1,0,-1,0 };
	int now = RIGHT;
	SNAKE_POS now_position = { 0,0 };
	SNAKE_LINE lines[1001];
	cin >> L >> R_count;
	long long time_count = 0;

	memset(rotate, 0, sizeof(rotate));
	fill(times, times + sizeof(times) / sizeof(long long), ((long long)2) * L + 1);
	for (int i = 0; i < R_count; i++)
	{
		cin >> times[i] >> rotate[i];
	}
	bool dead = false;

	int i = 0;
	SNAKE_POS prev;
	while(!dead)
	{
		prev = now_position;
		now_position.x += times[i]*dx[now];
		now_position.y += times[i]*dy[now];

		switch (now)
		{
		case UP:
			lines[i].end = now_position;
			lines[i].start = prev;
			lines[i].type = 'R';
			break;
		case DOWN:
			lines[i].start = now_position;
			lines[i].end = prev;
			lines[i].type = 'R';
			break;
		case LEFT:
			lines[i].start = now_position;
			lines[i].end = prev;
			lines[i].type = 'C';
			break;
		case RIGHT:
			lines[i].end = now_position;
			lines[i].start = prev;
			lines[i].type = 'C';
			break;
		}
		long long min_length = 2 * L + 1;
		for (int j = 0; j < i - 2; j++)
		{
			if (lines[i].IsCross(lines[j]))
			{
				dead = true;
				min_length = SNAKE_MIN(lines[j].GetLength(prev),min_length);
			}
		}
		if (dead)
		{
			length += min_length;
			break;
		}
		dead |= now_position.x < -1 * L || now_position.y < -1 * L;
		dead |= now_position.x > L || now_position.y > L;
		if (dead)
		{
			switch (now)
			{
			case UP:
				length += L - prev.y;
				break;
			case DOWN:
				length += prev.y + L;
				break;
			case LEFT:
				length += prev.x + L;
				break;
			case RIGHT:
				length += L - prev.x;
				break;
			}
			length++;
			break;
		}
		length += lines[i].GetLength();
		now = rotate[i] == 'L' ? (now + 3) % 4 : (rotate[i] == 'R' ? (now + 1) % 4 : now);
		i++;
	}

	cout << length << endl;
}