//와일드 카드
//알고스팟
//https://algospot.com/judge/problem/read/WILDCARD

#pragma once
#include<cstring>
#include<cstdio>

int check[100][100];
int len[51];
char str[51][101];
int n, t;

int strRes[50];
int temp[50];
int rIdx;

void init()
{
	scanf("%s\n", str[0]);

	scanf("%d\n", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%s\n", str[i]);
	}

	for (int i = 0; i <= n; i++)
	{
		len[i] = strlen(str[i]);
	}
	rIdx = 0;
}

bool match(int sIdx, int sLen, int wLen)
{
	if (sLen == len[sIdx] && wLen == len[0])
	{
		return true;
	}

	else if (sLen > len[sIdx] || wLen > len[0]) return false;

	if (check[sLen][wLen] != -1) return check[sLen][wLen];

	int ret = check[sLen][wLen];

	if (str[0][wLen] == '*')
	{
		return ret = match(sIdx, sLen, wLen + 1) || match(sIdx, sLen + 1,wLen);
	}

	if (str[0][wLen] != '?' && str[0][wLen] != str[sIdx][sLen])
	{
		check[sLen][wLen] = false;
		return false;
	}

	else
	{
		return check[sLen][wLen] = match(sIdx, sLen + 1, wLen + 1);
	}

	return false;
}


void merge(int left, int half, int right)
{
	int l = left, r = half + 1, k = left;

	while (l <= half && r <= right)
	{
		if (strcmp(str[strRes[l]], str[strRes[r]]) > 0)
		{
			temp[k++] = strRes[r++];
		}
		else
		{
			temp[k++] = strRes[l++];
		}
	}

	while (l <= half) temp[k++] = strRes[l++];
	while (r <= right) temp[k++] = strRes[r++];

	for (int i = left; i <= right; i++)
	{
		strRes[i] = temp[i];
	}
}

void mergeSort(int left, int right)
{
	if (left < right)
	{
		int half = (left + right) / 2;
		mergeSort(left, half);
		mergeSort(half + 1, right);

		merge(left, half, right);
	}
}

int WILDCARD()
{
	scanf("%d\n", &t);

	while (t--)
	{
		init();

		for (int i = 1; i <= n; i++)
		{
			memset(check, -1, sizeof(check));
			bool res = match(i, 0, 0);
			if (res)
			{
				strRes[rIdx++] = i;
			}
		}

		mergeSort(0, rIdx - 1);

		for (int i = 0; i < rIdx; i++)
		{
			printf("%s\n", str[strRes[i]]);
		}
	}

	return 0;
}