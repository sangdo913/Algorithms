#pragma once
#include<cstdio>
#include<cstring>

// Quantization
// ¾Ë°í½ºÆÌ
// https://algospot.com/judge/problem/read/QUANTIZE

int nums[101] = { 0 }, n, s;
int temp[101], memoi[11][101];
const int INF = 987654321;
int pSum[101] = { 0 }, p2Sum[101] = { 0 };

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

int sMin(int left, int right)
{
	int m = (int)((long long double(pSum[right] - pSum[left - 1])) / (right - left + 1) + 0.5);

	return p2Sum[right] - p2Sum[left - 1] - 2 * (pSum[right] - pSum[left - 1]) * m + m * m * (right - left + 1);
}

int getMin2(int cnt, int idx)
{
	int &ret = memoi[cnt][idx];

	if (ret != -1)
	{
		return ret;
	}

	if (idx == n)
	{
		return ret = 0;
	}

	if (cnt == 1)
	{
		return ret = sMin(idx, n);
	}

	ret = INF;

	for (int next = idx + 1; next <= n; next++)
	{
		ret = min(ret, sMin(idx, next - 1) + getMin2(cnt - 1, next));
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
		memset(pSum, 0, sizeof(pSum));
		memset(p2Sum, 0, sizeof(p2Sum));

		for (int i = 1; i <= n; i++)
		{
			pSum[i] += pSum[i - 1] + nums[i];
			p2Sum[i] += p2Sum[i - 1] + nums[i] * nums[i];
		}

		res = getMin2(s, 1);
		
		printf("%d\n", res);
	}

	return 0;
}