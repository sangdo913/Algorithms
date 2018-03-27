#pragma once
#include<iostream>
#include<string.h>
using namespace std;

struct BlockMeSang_Mesang
{
	int sum;
	int x;
	int y;
	int direct;
};

bool BlockMeSang_Bound(int x, int y,int n)
{
	return (x == 0) || (y == 0) || (x == n - 1) || (y == n - 1);
}

int BlockMeSang()
{
	typedef BlockMeSang_Mesang mesang;
	const int dx[5] = { 0,0,0,-1,1 };
	const int dy[5] = { 0,-1,1,0,0 };
	const int nextD[5] = { 0,2,1,4,3 };

	//�� ĭ�� �ִ� �̻����� ��
	int nextSum[100][100];
	//�� ĭ�� ������ �Ǵ� �̻��� ��ȣ
	int nextStd[100][100];

	mesang infos[1000];
	int t,n,k,m;
	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < k; i++)
		{
			scanf("%d %d %d %d", &infos[i].y, &(infos[i].x), &infos[i].sum, &infos[i].direct);
		}

		//�ð� üũ
		while (m--)
		{
			memset(nextSum, 0, sizeof(nextSum));
			memset(nextStd, -1, sizeof(nextStd));

			//�̻����� �̵�
			for (int i = 0; i < k; i++)
			{
				if (infos[i].sum == 0) continue;

				infos[i].x += dx[infos[i].direct];
				infos[i].y += dy[infos[i].direct];

				//���� ����
				if (BlockMeSang_Bound(infos[i].x, infos[i].y, n))
				{
					infos[i].direct = nextD[infos[i].direct];
					infos[i].sum /= 2;
				}

				//�ȴ���
				else
				{
					//����
					int min = nextStd[infos[i].y][infos[i].x];

					//1. ������ ������������ �̻��� �� ��ȣ�� �״�γִ´�.
					//2. ���غ��� ������ ������ �ֽ�ȭ�ϰ� ���ؿ� �ִ� �̻����� 0���� �����.
					//3. ���غ��� ���� ������ ���� ���� �̻����� 0���� �����.
					nextSum[infos[i].y][infos[i].x] += infos[i].sum;

					if (min == -1)
					{
						nextStd[infos[i].y][infos[i].x] = i;
					}
					else if ((infos[min].sum < infos[i].sum))
					{
						infos[min].sum = 0;
						nextStd[infos[i].y][infos[i].x] = i;
					}
					else
					{
						infos[i].sum = 0;
					}
				}
			}

			// �̻������� �ֽ�ȭ�Ѵ�.
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if(nextStd[i][j] != -1) infos[nextStd[i][j]].sum = nextSum[i][j];
		}

		int res = 0;

		for (int i = 0; i < k; i++)
		{
			res += infos[i].sum;
		}
		printf("#%d %d\n", tc, res);
	}
	return 0;
}