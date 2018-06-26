#pragma once
#include<cstring>
#include<cstdio>

int str[500001];

int suffix[500001], temp[500001];
int group[500001 << 1];
int tg[500001 << 1];

int n, m, t;

bool cmp(int left, int right)
{
	if (group[left] == group[right]) {
		return group[left + t] < group[right + t];
	}

	return group[left] < group[right];
}

void mergeSort(int left, int right, int m)
{
	int l = left, r = m + 1, k = left;

	while (l <= m && r <= right)
	{
		if (cmp(suffix[l], suffix[r])) {
			temp[k++] = suffix[l++];
		}
		else {
			temp[k++] = suffix[r++];
		}
	}

	while (l <= m) temp[k++] = suffix[l++];
	while (r <= right) temp[k++] = suffix[r++];

	for (int i = left; i <= right; i++) suffix[i] = temp[i];
}

void merge(int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, r, m);
	}
}

int FindSameSuffixArray()
{
	int te;
	scanf("%d\n", &te);

	for (int tc = 1; tc <= te; tc++)
	{
		scanf("%d %d\n", &n, &m);
		memset(group, 0, sizeof(group));

		for (int i = 0; i < n; i++)
		{
			scanf("%d \n", &str[i]);
		}

		for (int i = 0; i < n; i++)
		{
			suffix[i] = i;
			group[i] = str[i];
		}
		
		t = 1;
		while (t <= n)
		{
			merge(0, n - 1);

			tg[0] = 1;
			for (int i = 1; i < n; i++)
			{
				if (cmp(suffix[i - 1], suffix[i])) tg[suffix[i]] = tg[suffix[i - 1]] + 1;
				else {
					tg[suffix[i]] = tg[suffix[i - 1]];
				}
			}
			for (int i = 0; i < n; i++) group[i] = tg[i];
			t <<= 1;
		}

		int res = 0;
/*
		for (int i = 0; i < n; i++)
		{
			for (int j = suffix[i]; j < n; j++)
			{
				printf("%d", str[j]);
			}
			printf("\n");
		}

		printf("\n");

		for (int i = 0; i < n; i++)
		{
			printf("%d ", suffix[i]);
		}
		printf("\n");*/

		for (int i = 0; i < n - 1; i++)
		{
			res += str[suffix[i + 1]] - str[suffix[i]] - (suffix[i + 1] > suffix[i]);
		}
		res += m - str[n - 1];
		printf("#%d %d\n", tc, res);
	}
	return 0;
}