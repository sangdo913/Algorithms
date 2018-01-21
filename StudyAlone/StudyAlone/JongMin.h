#pragma once
/*
1857. 종민이의 도미노
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5Lpz56DwwDFAXc

알고리즘 :	맵을 입력받으면서 가로 도미노와 세로 도미노를 만든다.
			만들어진 도미노가 가릴 수 있는 값을 크기 순서대로 최대 30개까지 저장한다.
			조합을 이용해서 해당 도미노들로 가릴 수 있는 최대 값을 구한다.
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

//좌표 비교
bool DOMI_CompCOD(int x1, int y1, int x2, int y2)
{
	return x1 == x2 && y1 == y2;
}

//조합에서 선택된 도미노가 몇의 숫자를 가리는지 확인한다.
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

//30 개 중 격자판과 겹치지 않는 도미노를 구한다. (조합 응용)
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
			//겹침 체크
			isFold |= (JngMin_Check[b.y1][b.x1] || JngMin_Check[b.y2][b.x2]);
			//만약 겹치면, 이전 것 들을 다시 false로 돌려준다.
			if (isFold)
			{
				for(int j = i-1; j >= 0; j--)
				{
					b = JongMin_maxblocks[j + length];
					JngMin_Check[b.y2][b.x2] = JngMin_Check[b.y1][b.x1] = false;
				}
				break;
			}
			//안겹치면 맵에 체크하고 다시 다른것들도 겹치는지 확인한다.
			JngMin_Check[b.y1][b.x1] = JngMin_Check[b.y2][b.x2] = true;
		}

		if (isFold) return 0; //겹치면 끝장

		for (int i = 0; i < n; i++)
		{
			flag[length + i] = true;
		}
		int result = JongMin_nCr(size, flag); // 조합의 값 계산
		//리턴하기 전에 맵에 체크했던 것과 flag를 해제해준다.
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

	//도미노가 겹치는 경우에는 무조건 못 놓도록 한다.
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
				// 제일 중요한 부분은 입력을 받으면서 시간초과가 나기 때문에 scanf를 사용하거나 cin을 빠르게 하는 코드를 삽입한다.
				scanf("%d", &JongMin_MAP[i][j]);
				result += JongMin_MAP[i][j];

				// 세로 도미노
				// 맵을 집어 넣으면서 가릴수 있는 것이 최고로 높은 도미노 30개를 선정한다. 25개로 선정했을 때 틀린 테스트 케이스가 1개가 나와서 늘렸다.
				if (i > 1)
				{
					if (JongMin_maxblocks[JongMIN_ARR_SIZE-1].value < JongMin_MAP[i][j] + JongMin_MAP[i - 1][j])
					{
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x1 = j; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y1 = i;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].x2 = j; JongMin_maxblocks[JongMIN_ARR_SIZE-1].y2 = i-1;
						JongMin_maxblocks[JongMIN_ARR_SIZE-1].value = JongMin_MAP[i][j] + JongMin_MAP[i - 1][j];
						//계속해서 정렬해준다.
						sort(JongMin_maxblocks, JongMin_maxblocks + JongMIN_ARR_SIZE, greater<JongMin_BLOCK>());
						block_size++;
					}
				}

				//가로 도미노
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

		//사이즈는 최대 30까지
		block_size = block_size > JongMIN_ARR_SIZE ? JongMIN_ARR_SIZE : block_size;

		//선택된 조합이 무엇인지 저장해주는 배열
		bool flag[JongMIN_ARR_SIZE];
		memset(flag, false, sizeof(flag));

		result -= JongMin_GetMax(block_size, K, 0, flag, block_size);
		printf("#%d %d\n", tc, result);
	}
}