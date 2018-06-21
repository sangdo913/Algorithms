#pragma once
#include<cstdio>
#include<cstring>

long long k;
int lis[501][501], arr[501], lisLen[501];
int len[501], n; long long nums[501];


long long mod = 100000000000;

struct INFO
{
	int len;
	long long nums;
};

long long min(long long i1, long long i2)
{
	return i1 < i2 ? i1 : i2;
}

INFO getLIS(int idx)
{
	if (len[idx] != -1) return { len[idx], nums[idx] };

	INFO ret;

	len[idx] = 1;
	nums[idx] = 1;

	for (int i = idx + 1; i <= n; i++)
	{
		if (arr[idx] < arr[i])
		{
			ret = getLIS(i);

			if (ret.len + 1> len[idx])
			{
				len[idx] = ret.len + 1;
				nums[idx] = ret.nums;
				lis[idx][0] = i;
				lisLen[idx] = 1;
			}
			else if (ret.len + 1 == len[idx])
			{
				nums[idx] = min(nums[idx] + ret.nums, mod);
				
				lis[idx][lisLen[idx]++] = i;
			}
		}
	}

	return { len[idx], nums[idx] };
}

int temp[500];

void merge(int *a, int left, int m, int right)
{
	int l = left, r = m + 1, k = left;
	
	while (l <= m && r <= right)
	{
		if (arr[a[l]] < arr[a[r]])
		{
			temp[k++] = a[l++];
		}
		else
		{
			temp[k++] = a[r++];
		}
	}

	while (l <= m) temp[k++] = a[l++];
	while (r <= right) temp[k++] = a[r++];

	for (int i = left; i <= right; i++)
	{
		a[i] = temp[i];
	}
}

void mergeSort(int *arr, int left, int right)
{
	if (left < right)
	{
		int m = (left + right) / 2;

		mergeSort(arr, left, m);
		mergeSort(arr, m + 1, right);
		merge(arr, left, m, right);
	}
}

int res[500], rLen = 0;

void setRes(int idx, long long cnt)
{
	for (int j = 0; j < lisLen[idx]; j++)
	{
		if (cnt > nums[lis[idx][j]])
		{
			cnt -= nums[lis[idx][j]];
		}
		else
		{
			res[rLen++] = arr[lis[idx][j]];
			setRes(lis[idx][j], cnt);
			return;
		}
	}
}

int KLIS()
{
	int t;
	scanf("%d\n", &t);


	while (t--)
	{
		scanf("%d %lld\n", &n, &k);

		memset(lisLen, 0, sizeof(lisLen));
		memset(len, -1, sizeof(len));
		rLen = 0;

		for (int i = 1; i <= n; i++)
		{
			scanf("%d \n", &arr[i]);
		}

		INFO r = getLIS(0);
		r.len--;

		for (int i = 0; i <= n; i++)
		{
			mergeSort(lis[i], 0, lisLen[i]-1);
		}
		
		setRes(0, k);

		printf("%d\n", r.len);
		for(int i = 0; i < r.len; i++)
			printf("%d ", res[i]);

		printf("\n");
	}

	return 0;
}

