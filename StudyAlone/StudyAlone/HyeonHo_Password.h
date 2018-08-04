#pragma once
#include<iostream>

using namespace std;

char HyeonHo_initNums[15][51];
unsigned long long HyeonHo_memoi[1<<15][101];
int HyeonHo_nums[15];
int HyeonHo_sizeOfNum[15];
int HyeonHo_storeNums[15];
int HyeonHo_ind[15];
int HyeonHo_maxind;

 int HyeonHo_GetRemainder(char* str, int size, int K)
{
	int remainder = 0;
	for (int i = 0; i < size; i++)
	{
		remainder *= 10;
		remainder += str[i] - '0';
		remainder %= K;
	}
	return remainder % K;
}
 int HyeonHo_GetSize(char* str)
{
	int length = 0;
	while (*str)
	{
		length++;
		str++;
	}
	return length;
}
 inline void HeynHo_Init(int N, int K)
{
	for (int i = 0; i < N; i++)
	{
		HyeonHo_sizeOfNum[i] = HyeonHo_GetSize(HyeonHo_initNums[i]);
		HyeonHo_storeNums[i] = HyeonHo_nums[i] = HyeonHo_GetRemainder(HyeonHo_initNums[i],HyeonHo_sizeOfNum[i],K);
	}
	for (int i = 0; i < (1 << N); i++)
	{
		for (int j = 0; j < K; j++)
		{
				HyeonHo_memoi[i][j] = 0;
		}
		HyeonHo_memoi[i][100] = 0;
	}
	//for (int cnt = 0; cnt< N; cnt++)
	//{
	//	int i = 1 << cnt;
	//	HyeonHo_memoi[i][HyeonHo_nums[cnt]] = 1;
	//}

	for (int i = 0; i < 15; i++) HyeonHo_ind[i] = i;
}
inline void HyeonHo_swap(int ind1, int ind2)
{
	int temp, temp2;
	temp = HyeonHo_nums[ind1];
	temp2 = HyeonHo_ind[ind1];

	HyeonHo_ind[ind1] = HyeonHo_ind[ind2];
	HyeonHo_ind[ind2] = temp2;

	HyeonHo_nums[ind1] = HyeonHo_nums[ind2];
	HyeonHo_nums[ind2] = temp;

}

inline int HyeonHo_GetDigitByVisit(int visit)
{
	int ind = 0;
	int ret = 0;
	while (visit)
	{
		if (visit & 1)
		{
			ret +=HyeonHo_sizeOfNum[ind];
		}
		ind++;
		visit >>= 1;
	}
	return ret;
}
 inline int HyeonHo_GetExp(int digit, int K)
{
	int result = 1;
	int init = 10%K;

	while (digit)
	{
		result = digit & 1 ? result*init : result;
		result %= K;

		digit >>= 1;
		init *= init;
		init %= K;
	}
	return result;
}

void HyeonHo_GetPassword(int n, int r, int visit,int K, int prevRemainder)
{
	int tempRemainder;
	int nowVisit;
	int digit;
	int path = HyeonHo_maxind - visit;
	int indNum;
	int nextPath;

	if (n == r - 1)
	{
		int num = HyeonHo_nums[n]%K;

		HyeonHo_memoi[path][100] = 1;
		HyeonHo_memoi[path][num]++;
		return ;
	}

	for (int ind1 = n; ind1 < r; ind1++)
	{
			indNum = HyeonHo_ind[ind1];
	
			HyeonHo_swap(ind1, n);

			nowVisit = visit | (1 << indNum);
			nextPath = HyeonHo_maxind - nowVisit;

			digit = HyeonHo_sizeOfNum[HyeonHo_ind[n]];

			tempRemainder = prevRemainder;
			tempRemainder *= HyeonHo_GetExp(digit,K);
			tempRemainder += HyeonHo_nums[n];
			tempRemainder %= K;

			if(HyeonHo_memoi[nextPath][100] == 0 ) HyeonHo_GetPassword(n + 1, r, nowVisit, K, tempRemainder);
			
			digit = HyeonHo_GetDigitByVisit(nextPath);

			tempRemainder = HyeonHo_nums[n]* HyeonHo_GetExp(digit,K);
			tempRemainder %= K;

			tempRemainder;
			for (int k = 0; k < K; k++, tempRemainder++)
			{
				tempRemainder %= K;
				HyeonHo_memoi[path][tempRemainder] += HyeonHo_memoi[nextPath][k];
			}

			HyeonHo_swap(ind1, n);
	}

	HyeonHo_memoi[path][100] = 1;
	return;
}

inline int HyeonHo_GetBitNum(int num)
{
	int cnt = 0;
	while (num)
	{
		cnt= num & 1 ? ++cnt:cnt;
		num >>= 1;
	}
	return cnt;
}
inline int HyeonHo_nextBit(int bit, int num)
{
	if (bit == 0) return -1;
	bit--;
	int nextBit = 1 << (bit);
	while (nextBit && ((nextBit & num) == 0))
	{
		nextBit >>= 1;
		bit--;
	}
	return bit;
}

int HyeonHo_Pasword()
{
	int T, N, K;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		int numOfBit = 2;
		//init;
		scanf("%d", &N);
		HyeonHo_maxind = 1<<N;
		HyeonHo_maxind--;
		for (int i = 0; i < N; i++)
		{
			scanf("%s",HyeonHo_initNums[i]);
		}
		scanf("%d", &K);
		HeynHo_Init(N, K);

		//int digit,prevPath, bit;
		//int nextBit = 1; unsigned long long tempRemainder;
		//while (numOfBit <= N)
		//{
		//	for (int i = 3; i < (1 << N); i++)
		//	{
		//		if (HyeonHo_GetBitNum(i) != numOfBit) continue;
		//		nextBit = HyeonHo_nextBit(16,i);
		//		for (; nextBit != -1; nextBit = HyeonHo_nextBit(nextBit, i))
		//		{
		//			bit = 1 << nextBit;
		//			if (!(bit & i)) continue;
		//			prevPath = i - bit;

		//			digit = HyeonHo_GetDigitByVisit(prevPath);

		//			tempRemainder = HyeonHo_nums[nextBit] * HyeonHo_GetExp(digit, K);
		//			tempRemainder %= K;

		//			for (int k = 0; k < K; k++, tempRemainder++)
		//			{
		//				tempRemainder %= K;
		//				HyeonHo_memoi[i][tempRemainder] += HyeonHo_memoi[prevPath][k];
		//			}

		//		}
		//	}
		//	numOfBit++;
		//}
		HyeonHo_GetPassword(0, N, 0, K, 0);
		printf("#%d %lld\n", tc, HyeonHo_memoi[(1 << N) - 1][0]);
	}
	return 0;
}