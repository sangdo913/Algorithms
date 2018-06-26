#pragma once
#include<cstdio>
#include<cstring>

long long k;
//lis[x][y] : x에서 LIS를 위해서 방문해야하는 인덱스
// lisLen : x에서 LIS를 위해서 방문해야하는 인덱스의 개수
int lis[501][501], arr[501], lisLen[501];
//len : LIS의 길이, nums : 인덱스에서 만들어질 수 있는 경우의 수
int len[501], n; long long nums[501];

//오버플로우 방지
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

			//LIS 길이가 최신화 된 경우 전에 들어있던 인덱스를 모두 제거하고 길이를 1로 변경
			//가능한 경우의 수 최신화
			if (ret.len + 1> len[idx])
			{
				len[idx] = ret.len + 1;
				nums[idx] = ret.nums;
				lis[idx][0] = i;
				lisLen[idx] = 1;
			}
			//LIS 길이가 똑같은 경우 인덱스를 목록에 넣고 경우의 수 증가
			else if (ret.len + 1 == len[idx])
			{
				//오버 플로우 방지
				nums[idx] = min(nums[idx] + ret.nums, mod);
				
				//해당 인덱스를 lis목록에 넣고 길이 증가
				lis[idx][lisLen[idx]++] = i;
			}
		}
	}

	return { len[idx], nums[idx] };
}

int temp[500];

//정렬, lis에는 인덱스가 들어있으므로, arr[index]를 기준으로 정렬해야 한다!
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

// nums보다 cnt가 큰 경우 : 해당 nums 만큼 스킵가능
// nums보다 작거나 같은 경우 : 해당 인덱스 안에 cnt 번째 답이 있다!
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

