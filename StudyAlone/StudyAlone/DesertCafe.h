#pragma once
#include<iostream>

using namespace std;
struct DesertCafe_Cod
{
	int x; int y;
};

bool operator==(DesertCafe_Cod c1, DesertCafe_Cod c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}
struct DeserCafe
{
	int size;
	int map[22][22];
	bool visit[22][22];
	bool numVisit[101];
	const int dx[4] = { 1,1,-1,-1 };
	const int dy[4] = { -1,1,1,-1 };
	void clear()
	{
		for (int i = 0; i < 22; i++)
		{
			numVisit[i] = false;
			for (int j = 0; j < 22; j++)
			{
				visit[i][j] = false;
				map[i][j] = -1;
			}
		}
	}

	void init()
	{
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
				cin >> map[i][j];
		}
	}
}DesertCafe_info;

inline int Desert_GetMax(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

int GetMaxDesert(DesertCafe_Cod st, DesertCafe_Cod cod, int dir, int cnt)
{

	int ** map = (int**)DesertCafe_info.map;
	bool ** visit = (bool**)DesertCafe_info.visit;
	bool* numVisit = DesertCafe_info.numVisit;
	const int* dx = DesertCafe_info.dx;
	const int* dy = DesertCafe_info.dy;
	int size = DesertCafe_info.size;

	if (cod == st && dir == 3) return cnt;
	if (numVisit[(((int(*)[22])map)[cod.y][cod.x])] || ((int(*)[22])map)[cod.y][cod.x] == -1) return -1;
	int maxNum = -1;


	numVisit[((int(*)[22])map)[cod.y][cod.x]] = true;

	if (dir < 3) maxNum =  Desert_GetMax(maxNum, GetMaxDesert(st, { cod.x + dx[dir], cod.y + dy[dir] }, dir + 1, cnt + 1));

	maxNum = Desert_GetMax(maxNum, GetMaxDesert(st, { cod.x + dx[dir], cod.y + dy[dir] }, dir, cnt + 1));


	numVisit[((int(*)[22])map)[cod.y][cod.x]] = false;

	return maxNum;
}

int DesertCafe()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		int res = -1;
		cin >> DesertCafe_info.size;
		DesertCafe_info.clear();
		DesertCafe_info.init();
		for (int i = 2; i < DesertCafe_info.size; i++)
		{
			for (int j = 1; j < DesertCafe_info.size-1; j++)
				res = Desert_GetMax(res, GetMaxDesert({ j,i }, { j,i }, 0, 0));
		}

		printf("#%d %d\n", tc, res);
	}
	return 0;
}