#pragma once
#include<cstdio>
#include<cstring>

int cnum[26], len;
int  clen[11], cst[11], remain[11][10];

char selected[11], str[11], cnt[11][26];
int pelindrome() {
	int res = len;
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			bool isPelin = true;

			for (int k = 0; k <= (j - i) / 2; k++)
			{
				if (selected[i + k] != selected[j - k]) {
					isPelin = false;
					break;
				}
			}

			res += isPelin;
		}
	}
	return res;
}

int max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

int maxPelindrome(int depth)
{
	if (depth == len)
	{
		return pelindrome();
	}

	int ret = 0;
	for (int i = 1; i <= 10; i++)
	{
		if (cst[i] < clen[i])
		{
			selected[depth] = cnt[i][cst[i]];

			remain[i][cst[i]]--;
			if (remain[i][cst[i]] == 0) cst[i]++;

			ret = max(ret, maxPelindrome(depth + 1));

			if (cst[i] == clen[i] || remain[i][cst[i]] == i) cst[i]--;
			remain[i][cst[i]]++;
		}
	}
	return ret;
}

void init()
{
	memset(cnum, 0, sizeof(cnum));
	memset(clen, 0, sizeof(clen));
	memset(cst, 0, sizeof(cst));

	for (int i = 0; i < len; i++) cnum[str[i] - 'a']++;

	for (int i = 0; i < 26; i++)
	{
		cnt[cnum[i]][clen[cnum[i]]++] = i + 'a';
	}

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < clen[i]; j++)
		{
			remain[i][j] = i;
		}
	}
}

int SujinPelindrome()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		scanf("%s\n", str);
		len = strlen(str);

		init();

		int res = maxPelindrome(0);

		printf("#%d %d\n", tc, res);
	}
	return 0;
}