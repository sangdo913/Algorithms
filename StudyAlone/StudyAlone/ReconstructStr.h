#pragma once
#include<cstring>
#include<cstdio>

char str[30002];
char res[30002];

int ReconstructStr()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		int rLen = 0, sLen;
		int l, le, r, rs;

		scanf("%s\n", str);

		sLen = strlen(str);

		l = le = 0; r = rs = sLen - 1;

		while (rLen != sLen)
		{
			//대칭(홀수)
			if (rs == le)
			{
				res[rLen++] = str[r--];
				le = l;
				rs = r;

				//1 개남음
				if (r == l)
				{
					res[rLen++] = str[r];
				}

				continue;
			}
			//대칭(짝수)
			else if (rs < le)
			{
				res[rLen++] = str[l++];

				le = l;
				rs = r;

				continue;
			}

			//양쪽이 느림
			if (str[le] > str[l] && str[rs] > str[r])
			{
				res[rLen++] = str[l++];

				rs = r;
				le = l;

				continue;
			}

			// 양쪽이 빠르거나 같음
			else if (str[le] <= str[l] && str[rs] <= str[r])
			{
				//거기다 대칭
				if (str[le] == str[rs])
				{
					le++; rs--;

					continue;
				}
			}

			// 비대칭
			if (str[le] < str[rs])
			{

				res[rLen++] = str[l++];

				rs = r;
				le = l;
			}

			else
			{

				res[rLen++] = str[r--];

				rs = r;
				le = l;
			}
		}

		res[rLen] = 0;
		printf("#%d %s\n", tc, res);
	}

	return 0;
}