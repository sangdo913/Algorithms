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

//move[x,y][��ǥ] : ���� �������� �����ϱ� ���� �����ϴ°�
vector<int> moves[2][100001];
int temp[300000], sIdx[2][300000];// sidx[x,y][���ɹ�ȣ] : ������ x��ǥ�� y��ǥ���� �� ��°�� �ִ��� �����Ѵ�.
int maxF[300000]; // ���� ���ɿ��� ���� ���� �������� �����Ѵ�.
int yeonorder[300000],ytemp[300000]; // ������ ������ ������ �����Ѵ�.
int n,k;

//x�� ���� ���� ���� ������ �;��Ѵ�.
//x�� ���� ������ y�� ���� ���� ���� ������ �;��Ѵ�.
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

//��ü ������ �����ϴ� �κ�.
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
		//sIdx : �ڽ��� �ش� ��ǥ���� ���°���� �����Ѵ�.
		arr[i] = temp[i];
		sIdx[flag ^ 1][temp[i]] = i;
	}
}

//���� ������ �� �� �ֵ��� �����ϴ� �� flag�� ������ x���� �����ϴ� ��쿡�� y�� �������� �����ؾ��ϱ� �����̴�!
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
				//x ��ǥ�� ���� �̵��̶��, y ��ǥ�� �������� �����ؾ��Ѵ�.
				merge(moves[i][j], 0, moves[i][j].size() - 1, i^1);
			}
		}

		for (int i = 0; i < n; i++) yeonorder[i] = i;

		yeonmerge(0, n - 1);
		maxF[0] = yeons[0].f;

		for (int i = 0; i < n; i++) {
			int now = yeonorder[i];

			// n �� ���ɱ����� Ȯ���ϸ� �ȴ�.
			if (now == n - 1) break;

			//������ �� �� ����.
			if (maxF[now] < k) continue;
			//������ ���ؼ� �������� �Һ��ؾ��Ѵ�.
			maxF[now] -= k;

			for (int j = 0; j < 2; j++) {
				for (int idx = sIdx[j][now] + 1; idx < moves[j][yeons[now].pos[j]].size(); idx++) {
					int next = moves[j][yeons[now].pos[j]][idx];
					//�ִ� �������� �����Ѵ�.
					maxF[next] = max(maxF[next], maxF[now] + yeons[next].f);
				}
			}
		}
		//n�� ������ �ִ� �������� ����Ѵ�.
		printf("#%d %d\n", tc, maxF[n-1]);
	}
	return 0;
}