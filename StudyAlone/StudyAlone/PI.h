#pragma once
//원주율 외우기
//알고스팟
//https://algospot.com/judge/problem/read/PI

#include<cstdio>
#include<cstring>

char str[10001];
int dp[10001] = { 0 };

int min(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}

int abs(int i1)
{
	return i1 > 0 ? i1 : -i1;
}

int PI()
{
	int t;
	scanf("%d\n", &t);


	while (t--)
	{
		scanf("%s\n", str);

		int len = strlen(str);

		for (int i = 1; i <= len; i++)
		{
			dp[i] = 987654321;
		}

		for (int i = 0; i < len; i++)
		{
			char c[2];
			c[i%2] = str[i];
			c[(i+1)%2] = str[i + 1];

			int diff = str[i + 1] - str[i];
			bool hFlag[4] = { true, true, true, true };

			hFlag[0] = c[0] == c[1];
			hFlag[1] = abs(diff) == 1;

			for (int l = 2; l < 5; l++)
			{
				if (i + l >= len) break;
				int hard;

				hFlag[0] &= str[i + l] == str[i + l - 1];
				hFlag[1] &= str[i + l] - str[i + l - 1] == diff;
				hFlag[2] &= str[i + l] == c[(i + l) % 2];
				hFlag[3] &= str[i + l] - str[i + l - 1] == diff;

				if (hFlag[0]) hard = 1;
				else if (hFlag[1])
				{
					hard = 2;
				}
				else if (hFlag[2])
				{
					hard = 4;
				}
				else if (hFlag[3])
				{
					hard = 5;
				}
				else
				{
					hard = 10;
				}

				dp[i + l + 1] = min(dp[i + l + 1], dp[i] + hard);
			}
		}

		printf("%d\n", dp[len]);
	}
	return 0;
}