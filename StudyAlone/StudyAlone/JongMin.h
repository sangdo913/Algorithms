#pragma once
/*
1857. �������� ���̳�
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5Lpz56DwwDFAXc

�˰��� :	���� �Է¹����鼭 ���� ���̳�� ���� ���̳븦 �����.
			������� ���̳밡 ���� �� �ִ� ���� ũ�� ������� �ִ� 30������ �����Ѵ�.
			������ �̿��ؼ� �ش� ���̳��� ���� �� �ִ� �ִ� ���� ���Ѵ�.
*/
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<functional>
#define JongMIN_ARR_SIZE 30

using namespace std;
struct JongMin_BLOCK;
int JongMin_MAP[2002][2002];
bool JngMin_Check[2002][2002];

const int JongMIN_ROW = 0;
const int JongMIN_COL = 1;
struct JongMin_BLOCK
{
	int x1, x2, y1, y2;
	int value;

	JongMin_BLOCK(int x1, int x2, int y1, int y2, int value) : x1(x1), x2(x2), y1(y1), y2(y2), value(value) {}
	JongMin_BLOCK() { x1 = 0; x2 = 0; y1 = 0; y2 = 0; value = 0; }
};

bool operator>(JongMin_BLOCK b1, JongMin_BLOCK b2)
{
	return b1.value > b2.value;
}

JongMin_BLOCK JongMin_maxblocks[JongMIN_ARR_SIZE] = {};

int JongMin_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

//��ǥ ��
bool DOMI_CompCOD(int x1, int y1, int x2, int y2)
{
	return x1 == x2 && y1 == y2;
}

//���տ��� ���õ� ���̳밡 ���� ���ڸ� �������� Ȯ���Ѵ�.
int JongMin_nCr(int size, bool flag[JongMIN_ARR_SIZE])
{
	int result = 0;

	for (int i = 0; i < size; i++)
	{
		if (flag[i])
		{
			result += JongMin_maxblocks[i].value;
		}
	}
	return result;
}

//30 �� �� �����ǰ� ��ġ�� �ʴ� ���̳븦 ���Ѵ�. (���� ����)
int JongMin_GetMax(int n, int r, int length, bool flag[JongMIN_ARR_SIZE],int size)
{
	if (r == 0)
	{
		int result = JongMin_nCr(size, flag);
		return result;
	}
	else if (n == r)
	{
		bool isFold = false;
		JongMin_BLOCK b;
		for (int i = 0; i < n; i++)
		{
			b = JongMin_maxblocks[i + length];
			//��ħ üũ
			isFold |= (JngMin_Check[b.y1][b.x1] || JngMin_Check[b.y2][b.x2]);
			//���� ��ġ��, ���� �� ���� �ٽ� false�� �����ش�.
			if (isFold)
			{
				for(int j = i-1; j >= 0; j--)
				{
					b = JongMin_maxblocks[j + length];
					JngMin_Check[b.y2][b.x2] = JngMin_Check[b.y1][b.x1] = false;
				}
				break;
			}
			//�Ȱ�ġ�� �ʿ� üũ�ϰ� �ٽ� �ٸ��͵鵵 ��ġ���� Ȯ���Ѵ�.
			JngMin_Check[b.y1][b.x1] = JngMin_Check[b.y2][b.x2] = true;
		}

		if (isFold) return 0; //��ġ�� ����

		for (int i = 0; i < n; i++)
		{
			flag[length + i] = true;
		}
		int result = JongMin_nCr(size, flag); // ������ �� ���
		//�����ϱ� ���� �ʿ� üũ�ߴ� �Ͱ� flag�� �������ش�.
		for (int i = 0; i < n; i++)
		{
			b = JongMin_maxblocks[length + i];
			JngMin_Check[b.y2][b.x2] = JngMin_Check[b.y1][b.x1] = false;
			flag[length + i] = false;
		}
		return result;
	}
	int result = 0;
	JongMin_BLOCK b = JongMin_maxblocks[length];

	//���̳밡 ��ġ�� ��쿡�� ������ �� ������ �Ѵ�.
	if (!(JngMin_Check[b.y1][b.x1] || JngMin_Check[b.y2][b.x2]))
	{
		JngMin_Check[b.y1][b.x1] = true;
		JngMin_Check[b.y2][b.x2] = true;
		flag[length] = true;
		result = JongMin_MAX(result, JongMin_GetMax(n - 1, r - 1, length + 1, flag, size));
		JngMin_Check[b.y1][b.x1] = false;
		JngMin_Check[b.y2][b.x2] = false;
		flag[length] = false;
	}
	result = JongMin_MAX(result, JongMin_GetMax(n - 1, r, length + 1, flag, size));
	return result;
}

void JongMin_Domi()
{
	int T;
	scanf("%d", &T);
	int temp, N, K;
	for (int tc = 1; tc <= T; tc++)
	{
		int result = 0;
		memset(JongMin_MAP, -1, sizeof(JongMin_MAP));
		memset(JngMin_Check, false, sizeof(JngMin_Check));
		fill(JongMin_maxblocks, JongMin_maxblocks + JongMIN_ARR_SIZE, JongMin_BLOCK());
		scanf("%d %d", &N ,&K);
		int block_size = 0;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				// ���� �߿��� �κ��� �Է��� �����鼭 �ð��ʰ��� ���� ������ scanf�� ����ϰų� cin�� ������ �ϴ� �ڵ带 �����Ѵ�.
				scanf("%d", &JongMin_MAP[i][j]);
				result += JongMin_MAP[i][j];

				// ���� ���̳�
				// ���� ���� �����鼭 ������ �ִ� ���� �ְ�� ���� ���̳� 30���� �����Ѵ�. 25���� �������� �� Ʋ�� �׽�Ʈ ���̽��� 1���� ���ͼ� �÷ȴ�.
				if (i > 1)
				{
					if (JongMin_maxblocks[JongMIN_ARR_SIZE-1].value < JongMin_MAP[i][j] + JongMin_MAP[i - 1][j])
					{
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x1 = j; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y1 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x2 = j; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y2 = i-1;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].value = JongMin_MAP[i][j] + JongMin_MAP[i - 1][j];
						//����ؼ� �������ش�.
						sort(JongMin_maxblocks, JongMin_maxblocks + JongMIN_ARR_SIZE, greater<JongMin_BLOCK>());
						block_size++;
					}
				}

				//���� ���̳�
				if (j > 1)
				{
					if (JongMin_maxblocks[JongMIN_ARR_SIZE-1].value < JongMin_MAP[i][j] + JongMin_MAP[i][j-1])
					{
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x1 = j; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y1 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x2 = j-1; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y2 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].value = JongMin_MAP[i][j] + JongMin_MAP[i][j-1];
						sort(JongMin_maxblocks, JongMin_maxblocks + JongMIN_ARR_SIZE, greater<JongMin_BLOCK>());
						block_size++;
					}
				}
			}

		//������� �ִ� 30����
		block_size = block_size > JongMIN_ARR_SIZE ? JongMIN_ARR_SIZE : block_size;

		//���õ� ������ �������� �������ִ� �迭
		bool flag[JongMIN_ARR_SIZE];
		memset(flag, false, sizeof(flag));

		result -= JongMin_GetMax(block_size, K, 0, flag, block_size);
		printf("#%d %d\n", tc, result);
	}
}