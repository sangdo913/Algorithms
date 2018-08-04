#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<functional>

using namespace std;
struct JongMin_BLOCK;
int JongMin_MAP[2002][2002];
bool JngMin_Check[2002][2002];
int JongMin_VALUE = 0;

const int JongMIN_ROW = 0;
const int JongMIN_COL = 1;
int JongMin_ARR[2 * 2000 * 1999];
struct JongMin_BLOCK
{
	int x1, x2, y1, y2;
	int value;


	bool operator()(int i, int j);
	JongMin_BLOCK(int x1, int x2, int y1, int y2, int value) : x1(x1), x2(x2), y1(y1), y2(y2), value(value)
	{}
	JongMin_BLOCK() { x1 = 0; x2 = 0; y1 = 0; y2 = 0; value = 0; }
};

bool operator>(JongMin_BLOCK b1, JongMin_BLOCK b2)
{
	return b1.value > b2.value;
}
static JongMin_BLOCK JongMin_blocks[1999 * 2000 * 2] = {};

JongMin_BLOCK JongMin_maxblocks[25] = {};

bool JongMin_BLOCK::operator()(int i, int j)
{
	return JongMin_blocks[i] > JongMin_blocks[j];
}
//
//void JongMin_Get(int depth, int k, int value, int x, int y, int size)
//{
//	if (depth == k)
//	{
//		JongMin_VALUE = JongMin_VALUE < value ? value : JongMin_VALUE;
//		return;
//	}
//
//	int prev1; int prev2;
//	int x1, x2, y1, y2;
//	for (int i = y; i <= size; i++)
//	{
//		int j = y == i ? x : 1;
//		for (; j <= size; j++)
//		{
//			if (JongMin_MAP[i][j] < 0) break;
//			x1 = j; y1 = i; x2 = j + 1; y2 = i; // °¡·Î
//			if (JongMin_MAP[y2][x2] >= 0)
//			{
//				prev1 = JongMin_MAP[y1][x1];
//				prev2 = JongMin_MAP[y2][x2];
//				JongMin_MAP[y1][x1] = -1;
//				JongMin_MAP[y2][x2] = -1;
//				JongMin_Get(depth + 1, k, value + prev1 + prev2, x2+1, y2, size);
//				JongMin_MAP[y1][x1] = prev1;
//				JongMin_MAP[y2][x2] = prev2;
//			}
//			x2 = j; y2 = i + 1; // ¼¼·Î
//			if (JongMin_MAP[y2][x2] >= 0)
//			{
//				prev1 = JongMin_MAP[y1][x1];
//				prev2 = JongMin_MAP[y2][x2];
//				JongMin_MAP[y1][x1] = -1;
//				JongMin_MAP[y2][x2] = -1;
//				JongMin_Get(depth + 1, k, value + prev1 + prev2, x1 + 1, y1, size);
//				JongMin_MAP[y1][x1] = prev1;
//				JongMin_MAP[y2][x2] = prev2;
//			}
//		}
//	}
//
//}

void JongMin_Check(int size)
{
	int x1, x2, y1, y2, ind;
	for (int i = 1; i <= size; i++)
	{
		int j = 1;
		for (; j <= size; j++)
		{
			ind = (i - 1)*(size - 1) + j - 1;
			x1 = j; y1 = i; x2 = j + 1; y2 = i; // °¡·Î
			if (JongMin_MAP[y2][x2] >= 0)
			{
				JongMin_blocks[ind] = JongMin_BLOCK(x1, x2, y1, y2, JongMin_MAP[y1][x1] + JongMin_MAP[y2][x2]);
			}
			ind = (size - 1)*(size)+(i - 1)*(size)+j - 1;
			x2 = j; y2 = i + 1; // ¼¼·Î
			if (JongMin_MAP[y2][x2] >= 0)
			{
				JongMin_blocks[ind] = JongMin_BLOCK(x1, x2, y1, y2, JongMin_MAP[y1][x1] + JongMin_MAP[y2][x2]);
			}
		}
	}
}

int JongMin_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

bool DOMI_CompCOD(int x1, int y1, int x2, int y2)
{
	return x1 == x2 && y1 == y2;
}

int JongMin_nCr(int size, bool flag[25])
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

int JongMin_GetMax(int n, int r, int length, bool flag[25], int size)
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
			isFold |= (JngMin_Check[b.y1][b.x1] || JngMin_Check[b.y2][b.x2]);
			if (isFold)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					b = JongMin_maxblocks[j + length];
					JngMin_Check[b.y2][b.x2] = JngMin_Check[b.y1][b.x1] = false;
				}
				break;
			}
			JngMin_Check[b.y1][b.x1] = JngMin_Check[b.y2][b.x2] = true;
		}

		if (isFold) return 0;

		for (int i = 0; i < n; i++)
		{
			flag[length + i] = true;
		}
		int result = JongMin_nCr(size, flag);
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

//ind 1 : ÂïÈù ¾Ö ind2 ÂïÀ» ¾Ö
int JongMin_GetMAX(int K, int depth, int size, int value, int ind1, int ind2, int ARRsize)
{
	if (ind2 == ARRsize) return 0;
	if (K == depth) return value;
	int max = 0;

	typedef JongMin_BLOCK b;
	b b2 = JongMin_maxblocks[ind2];
	b b1 = JongMin_maxblocks[ind1];
	int x21 = b2.x1, x22 = b2.x2, y21 = b2.y1, y22 = b2.y2;
	int x11 = b1.x1, x12 = b1.x2, y11 = b1.y1, y12 = b1.y2, value1 = b1.value;
	int value2 = b2.value;


	if (!(JngMin_Check[y21][x21] || JngMin_Check[y22][x22]))
	{
		JngMin_Check[y11][x11] = true;
		JngMin_Check[y12][x12] = true;
		if (DOMI_CompCOD(x11, y11, x21, y21) || DOMI_CompCOD(x11, y11, x22, y22) || DOMI_CompCOD(x12, y12, x22, y22) || DOMI_CompCOD(x12, y12, x21, y21))
		{

			max = JongMin_MAX(max, JongMin_GetMAX(K, depth, size, value, ind1, ind2 + 1, ARRsize));


			JngMin_Check[y11][x11] = false;
			JngMin_Check[y12][x12] = false;

			JngMin_Check[y22][x22] = true;
			JngMin_Check[y21][x21] = true;
			max = JongMin_MAX(max, JongMin_GetMAX(K, depth, size, value + b2.value - b1.value, ind2, ind2 + 1, ARRsize));
			JngMin_Check[y22][x22] = false;
			JngMin_Check[y21][x21] = false;
		}

		else
		{
			JngMin_Check[y21][x21] = true;
			JngMin_Check[y22][x22] = true;
			max = JongMin_MAX(max, JongMin_GetMAX(K, depth + 1, size, value + b2.value, ind2, ind2 + 1, ARRsize));
			JngMin_Check[y21][x21] = false;
			JngMin_Check[y22][x22] = false;
		}
	}
	else
	{
		max = JongMin_MAX(max, JongMin_GetMAX(K, depth, size, value, ind1, ind2 + 1, ARRsize));
	}

	return max;
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
		//memset(JongMin_ARR, 0, sizeof(JongMin_ARR));

		priority_queue<JongMin_BLOCK> pq;
		memset(JngMin_Check, false, sizeof(JngMin_Check));
		fill(JongMin_maxblocks, JongMin_maxblocks + 25, JongMin_BLOCK());
		scanf("%d %d", &N, &K);
		//for (int i = 1; i < N*(N - 1) * 2; i++)
		//{
		//	JongMin_ARR[i] = i;
		//}
		//JongMin_VALUE = 0;
		int block_size = 0;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				scanf("%d", &JongMin_MAP[i][j]);
				result += JongMin_MAP[i][j];
				if (i > 1)
				{
					if (JongMin_maxblocks[24].value < JongMin_MAP[i][j] + JongMin_MAP[i - 1][j])
					{
						JongMin_maxblocks[24].x1 = j; JongMin_maxblocks[24].y1 = i;
						JongMin_maxblocks[24].x2 = j; JongMin_maxblocks[24].y2 = i - 1;
						JongMin_maxblocks[24].value = JongMin_MAP[i][j] + JongMin_MAP[i - 1][j];
						sort(JongMin_maxblocks, JongMin_maxblocks + 25, greater<JongMin_BLOCK>());
						block_size++;
					}
				}

				if (j > 1)
				{
					if (JongMin_maxblocks[24].value < JongMin_MAP[i][j] + JongMin_MAP[i][j - 1])
					{
						JongMin_maxblocks[24].x1 = j; JongMin_maxblocks[24].y1 = i;
						JongMin_maxblocks[24].x2 = j - 1; JongMin_maxblocks[24].y2 = i;
						JongMin_maxblocks[24].value = JongMin_MAP[i][j] + JongMin_MAP[i][j - 1];
						sort(JongMin_maxblocks, JongMin_maxblocks + 25, greater<JongMin_BLOCK>());
						block_size++;
					}
				}
			}
		//JongMin_Check(N);

		//sort(JongMin_ARR, JongMin_ARR + N*(N - 1) * 2, JongMin_BLOCK());
		block_size = block_size > 25 ? 25 : block_size;
		JongMin_BLOCK first = JongMin_maxblocks[0];
		//JongMin_Get(0, K, 0, 1, 1, N);

		//result -=  JongMin_GetMAX(K, 1, N, first.value, 0, 1,block_size);//JongMin_VALUE;//
		bool flag[25];
		memset(flag, false, sizeof(flag));
		result -= JongMin_GetMax(block_size, K, 0, flag, block_size);
		printf("#%d %d\n", tc, result);
	}
}