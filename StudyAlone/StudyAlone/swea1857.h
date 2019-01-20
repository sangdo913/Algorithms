
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
int JongMin_VALUE = 0;

const int JongMIN_ROW = 0;
const int JongMIN_COL = 1;
struct JongMin_BLOCK
{
	int x1, x2, y1, y2;
	int value;

	JongMin_BLOCK(int x1, int x2, int y1, int y2, int value) : x1(x1), x2(x2), y1(y1), y2(y2), value(value)
	{}
	JongMin_BLOCK() { x1 = 0; x2 = 0; y1 = 0; y2 = 0; value = 0; }
};

bool operator>(const JongMin_BLOCK& b1, const JongMin_BLOCK& b2)
{
	return b1.value > b2.value;
}

JongMin_BLOCK JongMin_maxblocks[JongMIN_ARR_SIZE+1] = {};

int JongMin_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

bool DOMI_CompCOD(int x1, int y1, int x2, int y2)
{
	return x1 == x2 && y1 == y2;
}

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
			isFold |= (JngMin_Check[b.y1][b.x1] || JngMin_Check[b.y2][b.x2]);
			if (isFold)
			{
				for(int j = i-1; j >= 0; j--)
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
        memset(JongMin_maxblocks, 0,sizeof(JongMin_maxblocks));

		scanf("%d %d", &N ,&K);
        JongMin_BLOCK temp;
        
		int block_size = 0;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
			{
				scanf("%d", &JongMin_MAP[i][j]);
				result += JongMin_MAP[i][j];
				if (i > 1)
				{
						JongMin_maxblocks[JongMIN_ARR_SIZE].x1 = j; JongMin_maxblocks[JongMIN_ARR_SIZE].y1 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE].x2 = j; JongMin_maxblocks[JongMIN_ARR_SIZE].y2 = i-1;
						JongMin_maxblocks[JongMIN_ARR_SIZE].value = JongMin_MAP[i][j] + JongMin_MAP[i - 1][j];

                        int k = JongMIN_ARR_SIZE;
                        while(k && JongMin_maxblocks[k] > JongMin_maxblocks[k-1]){
                             temp = JongMin_maxblocks[k];
                             JongMin_maxblocks[k] = JongMin_maxblocks[k-1];
                             JongMin_maxblocks[k-1] = temp;
                             k--;
                        }
						block_size++;
				}

				if (j > 1)
				{
						JongMin_maxblocks[JongMIN_ARR_SIZE].x1 = j; JongMin_maxblocks[JongMIN_ARR_SIZE].y1 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE].x2 = j-1; JongMin_maxblocks[JongMIN_ARR_SIZE].y2 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE].value = JongMin_MAP[i][j] + JongMin_MAP[i][j-1];
                        int k = JongMIN_ARR_SIZE;
                        while(k && JongMin_maxblocks[k] > JongMin_maxblocks[k-1]){
                            temp = JongMin_maxblocks[k];
                            JongMin_maxblocks[k] = JongMin_maxblocks[k-1];
                            JongMin_maxblocks[k-1] = temp;
                            k--;
                        }
						block_size++;
				}
			}

		block_size = block_size > JongMIN_ARR_SIZE ? JongMIN_ARR_SIZE : block_size;
		JongMin_BLOCK first = JongMin_maxblocks[0];

		bool flag[JongMIN_ARR_SIZE];
		memset(flag, false, sizeof(flag));
		result -= JongMin_GetMax(block_size, K, 0, flag, block_size);
		printf("#%d %d\n", tc, result);
	}
}
int Do()
{
    JongMin_Domi();
    return 0;
}