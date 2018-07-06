#pragma once
#include<cstdio>
#include<cstring>

int n;
char str[16][41], res[1000], tstr[16][41];
int mlen[16][1 << 15], len[16], tlen[16], order[16], temp[16];
int to[16][16], path[16][1 << 15];

int min(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}

int getLen(int idx, int visit)
{
	if (visit == (1 << n) - 1)
	{
		path[idx][visit] = 0;
		return 0;
	}

	int &ret = mlen[idx][visit];
	if (ret != -1) return ret;

	ret = 987654321;

	for (int next = 0; next < n; next++)
	{
		if ((1 << next) & visit) continue; //이미 방문한 인덱스

		int dist = getLen(next + 1, visit | (1 << next)) - to[idx][next + 1] + len[next + 1];
		
		if (dist < ret)
		{
			path[idx][visit] = next + 1;
			ret = dist;
		}
	}

	return ret;
}

//길이가 긴 순서대로 merge
void mergeSort(int left, int m, int right)
{
	int l = left, r = m + 1, k = l;

	while (l <= m && r <= right)
	{
		if (len[l] < len[r])
		{
			tlen[k] = len[r];
			temp[k++] = order[r++];
		}
		else
		{
			tlen[k] = len[l];
			temp[k++] = order[l++];
		}
	}

	while (l <= m) {
		tlen[k] = len[l];
		temp[k++] = order[l++];
	}

	while (r <= right) {
		tlen[k] = len[r];
		temp[k++] = order[r++];
	}

	for (int i = left; i <= right; i++) {
		len[i] = tlen[i];
		order[i] = temp[i];
	}
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, m, r);
	}
}

//경로 탐색 만약 경로면 다음 문자열과 겹치기 전 부분까지만 출력!
void setRes(int idx, int visit, int &l)
{
	int next = path[idx][visit];

	for (int i = 0; i < len[idx] - to[idx][next]; i++)
	{
		res[l++] = str[idx][i];
	}
	if(visit != (1 << n) - 1) setRes(next, visit | (1 << (next - 1)), l);
}

void init()
{
	//포함되는지 검사
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n;)
		{
			bool part = false;
			for (int k = 0; k <= len[i] - len[j]; k++)
			{
				bool same = true;
				for (int l = 0; l < len[j]; l++)
				{
					if (str[i][k + l] != str[j][l])
					{
						same = false; 
						break;
					}
				}
				if (same)
				{
					part = true;
					break;
				}
			}

			//포함된다면 해당 문자열 삭제
			if (part)
			{
				for (int k = j; k < n; k++)
				{
					memcpy(str[k], str[k + 1], sizeof(str[k]));
					len[k] = len[k + 1];
				}
				n--;
			}
			else
			{
				j++;
			}
		}
	}

	memset(to, 0, sizeof(to));
	memset(mlen, -1, sizeof(mlen));
	memset(path, 0, sizeof(path));

	//겹치는 길이 검사
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;
			int st = 0 > len[i] - len[j] + 1 ? 0 : len[i] - len[j] + 1;
			
			int k;
			for (k = st; k < len[i]; k++)
			{
				bool allsame = true;
				for (int l = 0; k + l < len[i]; l++)
				{
					if (str[i][k + l] != str[j][l])
					{
						allsame = false;
						break;
					}
				}
				if (allsame)
				{
					break;
				}
			}

			to[i][j] = len[i] - k;
		}
	}
}

int RESTORE()
{
	int tc;
	scanf("%d\n", &tc);

	while (tc--)
	{

		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++)
		{
			order[i] = i;
			scanf("%s\n", str[i]);
			len[i] = strlen(str[i]);
		}

		merge(1, n);

		for (int i = 1; i <= n; i++)
		{
			memcpy(tstr[i], str[order[i]], sizeof(tstr[i]));
		}

		memcpy(str, tstr, sizeof(str));
		
		init();
		int idx = getLen(0, 0);
		int l = 0;
		setRes(0, 0, l);
		res[l] = 0;

		printf("%s\n", res);
	}
	return 0;
}