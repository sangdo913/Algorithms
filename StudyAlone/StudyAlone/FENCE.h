//FENCE : 울타리 잘라내기
//알고스팟
//https://algospot.com/judge/problem/read/FENCE

#pragma once
#include<cstdio>

int h[20000];

int getMax(int i1, int i2, int i3)
{
	if (i1 > i2)
	{
		return i1 > i3 ? i1 : i3;
	}

	else
	{
		return i2 > i3 ? i2 : i3;
	}
}

int getMin(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}

int getMaxArea(int left, int right)
{
	if (left + 1 == right)
	{
		return h[left];
	}

	int half = (left + right) / 2;
	int s = 0, area = 0, l = half - 1 , r = half, blockNum = 0;
	int minH = getMin(h[l], h[r]);

	while (l >= left && r < right)
	{
		blockNum++;

		if (h[l] > h[r])
		{
			minH = getMin(minH, h[l--]);
			s = blockNum * minH;
			area = area > s ? area : s;
		}
		else
		{
			minH = getMin(minH, h[r++]);
			s = blockNum * minH;
			area = area > s ? area : s;
		}
	}
	
	while (l >= left)
	{
		blockNum++;
		minH = getMin(minH, h[l--]);
		s = blockNum * minH;
		area = area > s ? area : s;
	}

	while (r < right)
	{
		blockNum++;
		minH = getMin(minH, h[r++]);
		s = blockNum * minH;
		area = area > s ? area : s;
	}

	return getMax(getMaxArea(left, half), getMaxArea(half, right), area);
}

int FENCE()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		int n;
		scanf("%d\n", &n);

		for (int i = 0; i < n; i++)
		{
			scanf("%d \n", h + i);
		}

		printf("%d\n", getMaxArea(0, n));
	}
	return 0;
}