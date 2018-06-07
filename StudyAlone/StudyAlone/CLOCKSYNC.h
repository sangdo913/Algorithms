#include<stdio.h>
#include<string.h>

int clocks[16];
int cntNum[10];
const int swNum[10] = { 3,4,4,5,5,4,3,5,5,5 };
const int swch[10][5] = { {0,1,2}, {3,7,9,11}, {4,10,14,15}, {0,4,5,6,7}, {6,7,8,10,12}, {0,2,14,15}, {3,14,15}, {4,5,7,14,15}, {1,2,3,4,5}, {3,4,5,9,13} };
int swCnt[10];
const int INF = 987654321;
int min;

int check()
{
	int clockTemp[16];

	memcpy(clockTemp, clocks, sizeof(clocks));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < swNum[i]; j++)
		{
			clockTemp[swch[i][j]]+= cntNum[i];
		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (clockTemp[i] % 4) return 0;
	}
	return 1;
}

int switchOn(int cnt,int now)
{
	if (cnt >= min) return 0;

	if (now == 10)
	{
		if (check())
		{
			min = min > cnt ? cnt : min;
			return 1;
		}
		
		return 0;
	}

	int res = 0;

	for (int i = 0; i < 4; i++)
	{
		cntNum[now] = i;
		res += switchOn(cnt + i, now + 1);
	}
	return res;
}

int CLOCKSYNC()
{
	int c;
	scanf("%d\n", &c);

	while (c--)
	{
		memset(swCnt, 0, sizeof(swCnt));
		min = INF;

		for (int i = 0; i < 16; i++)
		{
			scanf("%d \n", clocks + i);
			clocks[i] = (clocks[i] / 3) % 4;
		}

		if (switchOn(0,0))
		{
			printf("%d\n", min);
		}
		else
		{
			printf("%d\n", -1);
		}
	}
	return 0;
}