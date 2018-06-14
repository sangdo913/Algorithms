#pragma once
#include<cstdio>
#include<cstring>

// Quantization
// ¾Ë°í½ºÆÌ
// https://algospot.com/judge/problem/read/QUANTIZE

int nums[101] = { 0 }, n, s;
int temp[101], memoi[11][101], cache[1001][101];
const int INF = 987654321;

int min(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}

void merge(int left, int m, int right)
{
	int l = left, r = m + 1, k = left;

	while (l <= m && r <= right)
	{
		if (nums[l] < nums[r])
		{
			temp[k++] = nums[l++];
		}
		else
		{
			temp[k++] = nums[r++];
		}
	}

	while (l <= m) temp[k++] = nums[l++];
	while (r <= right) temp[k++] = nums[r++];

	for (int i = left; i <= right; i++)
	{
		nums[i] = temp[i];
	}
}

void mergeSort(int left, int right)
{
	if (left < right)
	{
		int m = (left + right) / 2;
		mergeSort(left, m);
		mergeSort(m + 1, right);

		merge(left, m, right);
	}
}

int getMin(int cnt, int idx)
{
	int& ret = memoi[cnt][idx];
	if (ret != -1) return ret;

	ret = INF;

	if (cnt == 1)
	{
		for (int p = 1; p <= 1000; p++)
		{
			ret = min(cache[p][n] - cache[p][idx - 1], ret);
		}

		return ret;
	}

	if (idx == n) return ret = 0;

	int p;

	for (int i = 1; i <= nums[n]; i++)
	{
		for (int j = idx + 1; j <= n; j++)
		{
			p = cache[i][j - 1] - cache[i][idx - 1];

			ret = min(ret, p + getMin(cnt - 1, j));
		}
	}

	return ret;
}

void init()
{
	scanf("%d %d\n", &n, &s);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d \n", &nums[i]);
	}
	mergeSort(1, n);
}

int QUANTIZE()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		init();

		int res = INF;
		memset(memoi, -1, sizeof(memoi)); 

		for (int p = 1; p <= 1000; p++)
		{
			cache[p][1] = (nums[1] - p) * (nums[1] - p);

			for (int i = 2; i <= n; i++)
			{
				cache[p][i] = cache[p][i - 1] + (nums[i] - p) * (nums[i] - p);
			}
		}

		res = getMin(s, 1);
		
		printf("%d\n", res);
	}
	return 0;
}