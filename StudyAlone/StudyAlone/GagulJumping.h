#pragma once
#include<cstdio>
#include<vector>
#include<cstring>
#include<map>
#include<algorithm>

using namespace std;

struct YEON
{
	int pos[2], f;
} yeons[300000];

vector<int> moves[2][100001];
int temp[300000], sIdx[2][300000];
map<pair<int, int> , int> memoi;
typedef map<pair<int, int>, int> MII;
int n,k;



void mergeSort(vector<int>& arr, int left, int right, int m, int flag)
{
	int l = left, k = left, r = m + 1;

	while (l <= m && r <= right)
	{
		if (yeons[arr[l]].pos[flag] < yeons[arr[r]].pos[flag]) temp[k++] = arr[l++];
		else
		{
			temp[k++] = arr[r++];
		}
	}

	while (l <= m) temp[k++] = arr[l++];
	while (r <= right) temp[k++] = arr[r++];

	for (int i = left; i <= right; i++)
	{
		arr[i] = temp[i];
		sIdx[flag ^ 1][temp[i]] = i;
	}
}

void merge(vector<int>& arr, int left, int right, int flag)
{

	if (left < right)
	{
		int m = (left + right) / 2;

		merge(arr, left, m, flag);
		merge(arr, m + 1, right, flag);
		mergeSort(arr, left, right, m, flag);
	}
}

int max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

int GetMaxFly(int num, int f)
{
	if (num == n - 1) return yeons[num].f;

	MII::iterator it = memoi.find(make_pair(f, num));
	int& ret = it->second;
	if (it != memoi.end()) return ret = it->second;
	
	ret = -100;
	f += yeons[num].f - k;

	if (f < 0) return ret;

	for (int i = 0; i < 2; i++)
	{
		for (int j = sIdx[i][num] + 1; j < moves[i][yeons[num].pos[i]].size(); j++)
		{
			int nYeon = moves[i][yeons[num].pos[i]][j];

			ret = max(ret, GetMaxFly(nYeon, f));
		}
	}

	ret = ret > 0 ? ret + yeons[num].f : -100;

	return ret;
}

int GagulJumping()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%d %d\n", &n, &k);

		memoi.clear();

		for (int i = 0; i < n; i++)
		{
			scanf("%d %d %d\n", &yeons[i].pos[0], &yeons[i].pos[1], &yeons[i].f);
			moves[0][yeons[i].pos[0]].push_back(i);
			moves[1][yeons[i].pos[1]].push_back(i);
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 100001; j++)
			{
				merge(moves[i][j], 0, moves[i][j].size() - 1, i^1);
			}
		}

		int res = GetMaxFly(0, 0);
		printf("#%d %d\n", tc, res);
	}
	return 0;
}