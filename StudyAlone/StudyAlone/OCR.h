#pragma once
#include<cstdio>
#include<cstring>

char str[501][11], qStr[100][11];

int sIdx[501], temp[501], qIdx[101], m, n, q;

double T[501][501];
double M[501][501];

double cache[501][101];
int choice[501][101], res[100], rLen;

void mergeSort(int left, int m, int right)
{
	int l = left, r = m + 1, k = left;
	
	while (l <= m && r <= right)
	{
		if (strcmp(str[sIdx[l]], str[sIdx[r]]) < 0)
		{
			temp[k++] = sIdx[l++];
		}
		else
		{
			temp[k++] = sIdx[r++];
		}
	}

	while (l <= m) temp[k++] = sIdx[l++];
	while (r <= right) temp[k++] = sIdx[r++];

	for (int i = left; i <= right; i++)
	{
		sIdx[i] = temp[i];
	}
}

void merge(int left, int right)
{
	if (left < right)
	{
		int m = (left + right) / 2;
		merge(left, m);
		merge(m + 1, right);
		mergeSort(left, m, right);
	}
}

int find(const char* s)
{
	int l = 1, r = m;
	
	while (l <= r)
	{
		int m = (l + r) / 2;
		
		int res = strcmp(str[sIdx[m]], s);
		if (res == 0)
		{
			return sIdx[m];
		}
		else if (res < 0)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}

	}
	return -1;
}

double ocr(int prev, int now)
{
	if (now > n)
	{
		return 1.0;
	}

	double &ret = cache[prev][now];
	
	if (ret > -0.5) return ret;
	ret = 0;
	double temp1, tP;

	for (int i = 1; i <= m; i++)
	{
		double p = M[i][qIdx[now]];
		temp1 = T[prev][i];
		tP = p * temp1 * ocr(i, now + 1);
		if (ret < tP)
		{
			ret = tP;
			choice[prev][now] = i;
		}
	}

	return ret;
}

void print(int prev, int now)
{
	res[rLen++] = choice[prev][now];

	if (now == n)
	{
		return;
	}

	print(choice[prev][now], now + 1);
}

int OCR()
{
	scanf("%d %d\n", &m, &q);

	for (int i = 1; i <= m; i++)
	{
		scanf("%s \n", str[i]);
	}

	for (int i = 0; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%lf \n", &T[i][j]);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%lf \n", &M[i][j]);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		sIdx[i] = i;
	}

	merge(1, m);

	while (q--)
	{
		scanf("%d\n", &n);

		for (int i = 1; i <= n; i++)
		{
			scanf("%s \n", qStr[i]);
		}

		for (int i = 1; i <= n; i++)
		{
			qIdx[i] = find(qStr[i]);
		}

		for (int i = 0; i <= m; i++) 
			for (int j = 0; j <= n; j++)
			{
				choice[i][j] = -1;
				cache[i][j] = -1;
			}

		ocr(0, 1);

		rLen = 0;
		print(0, 1);

		for (int i = 0; i < rLen; i++) printf("%s ", str[res[i]]);
		printf("\n");
	}
	return 0;
}