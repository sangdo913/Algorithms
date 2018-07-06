#pragma once
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cstring>

using namespace std;

struct YEON
{
	int pos[2], f;
} yeons[300000];

//move[x,y][좌표] : 다음 연꽃으로 점프하기 위해 정렬하는곳
vector<int> moves[2][100001];
int temp[300000], sIdx[2][300000];// sidx[x,y][연꽃번호] : 연꽃이 x좌표나 y좌표에서 몇 번째에 있는지 저장한다.
int maxF[300000]; // 현재 연꽃에서 가장 많은 에너지를 저장한다.
int yeonorder[300000],ytemp[300000]; // 연꽃을 정렬한 정보를 저장한다.
int n,k;

//x의 값이 작은 것이 앞으로 와야한다.
//x의 값이 같으면 y의 값이 작은 것이 앞으로 와야한다.
bool comp(int i1, int i2) {
	if (yeons[i1].pos[0] < yeons[i2].pos[0]) {
		return true;
	}
	else if (yeons[i1].pos[0] == yeons[i2].pos[0])
	{
		return yeons[i1].pos[1] < yeons[i2].pos[1];
	}
	else
	{
		return false;
	}
}

void yeonSort(int left, int m, int right)
{
	int l = left, r = m + 1, k = l;
	while (l <= m && r <= right)
	{
		if (comp(yeonorder[l], yeonorder[r])) {
			ytemp[k++] = yeonorder[l++];
		}
		else {
			ytemp[k++] = yeonorder[r++];
		}
	}

	while (l <= m) ytemp[k++] = yeonorder[l++];
	while (r <= right) ytemp[k++] = yeonorder[r++];

	for (int i = left; i <= right; i++) yeonorder[i] = ytemp[i];
}

//전체 연꽃을 정렬하는 부분.
void yeonmerge(int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		yeonmerge(l, m);
		yeonmerge(m + 1, r);
		yeonSort(l, m, r);
	}
}


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
		//sIdx : 자신이 해당 좌표에서 몇번째인지 저장한다.
		arr[i] = temp[i];
		sIdx[flag ^ 1][temp[i]] = i;
	}
}

//다음 연꽃을 뛸 수 있도록 정렬하는 곳 flag의 이유는 x에서 점프하는 경우에는 y를 기준으로 정렬해야하기 때문이다!
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

int GagulJumping()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		memset(maxF, -1, sizeof(maxF));
		scanf("%d %d\n", &n, &k);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 100001; j++)
			{
				moves[i][j].clear();
			}
		}

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
				//x 좌표에 대한 이동이라면, y 좌표를 기준으로 정렬해야한다.
				merge(moves[i][j], 0, moves[i][j].size() - 1, i^1);
			}
		}

		for (int i = 0; i < n; i++) yeonorder[i] = i;

		yeonmerge(0, n - 1);
		maxF[0] = yeons[0].f;

		for (int i = 0; i < n; i++) {
			int now = yeonorder[i];

			// n 번 연꽃까지만 확인하면 된다.
			if (now == n - 1) break;

			//점프를 할 수 없다.
			if (maxF[now] < k) continue;
			//점프를 위해서 에너지를 소비해야한다.
			maxF[now] -= k;

			for (int j = 0; j < 2; j++) {
				for (int idx = sIdx[j][now] + 1; idx < moves[j][yeons[now].pos[j]].size(); idx++) {
					int next = moves[j][yeons[now].pos[j]][idx];
					//최대 에너지를 수정한다.
					maxF[next] = max(maxF[next], maxF[now] + yeons[next].f);
				}
			}
		}
		//n번 연꽃의 최대 에너지를 출력한다.
		printf("#%d %d\n", tc, maxF[n-1]);
	}
	return 0;
}