// �ִ� ���� �κ� ����
// �˰���
// https://algospot.com/judge/problem/read/LIS

#pragma once
#include<cstdio>
#include<cstring>

int t, arr[500], n;
int res[501], rIdx;

//���̳ʸ� ��ġ
//���� lis ������ �ϼ��� ������ ���� �Էµ� ������ ũ�ų� ���� ���� ��ġ ��ȯ
int bs(int v)
{
	int m;
	int l = 0, r = rIdx;
	while (l <= r)
	{
		int m = (l + r) / 2;
		if (res[m] >= v)
		{
			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}

	return r + 1;
}

void init()
{
	memset(res, 0, sizeof(res));
	rIdx = 0;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d \n", &arr[i]);
	}
}

int LIS()
{
	scanf("%d\n", &t);
	while (t--)
	{
		init();
		for (int i = 0; i < n; i++)
		{
			int idx = bs(arr[i]);
			rIdx = rIdx < idx ? idx : rIdx;

			res[idx] = arr[i];
		}

		printf("%d\n", rIdx);
	}
	return 0;
}