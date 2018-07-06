#pragma once
#include<cstdio>
#include<cstring>

int hypoons[21];
char str[21];
char res[121];

int ElongatedSound()
{
	int tc;
	scanf("%d\n", &tc);

	for (int t = 1; t <= tc; t++)
	{
		memset(hypoons, 0, sizeof(hypoons));

		scanf("%s\n", str);
		int len = strlen(str);
		int n;
		scanf("%d\n", &n);
		while (n--)
		{
			int in;
			scanf("%d \n", &in);
			hypoons[in]++;
		}
		int rlen = 0;

		for (int i = 0; i < len; i++)
		{
			while (hypoons[i]--) res[rlen++] = '-';
			res[rlen++] = str[i];
		}

		while (hypoons[len]--) res[rlen++] = '-';

		res[rlen] = 0;
		printf("#%d %s\n",t, res);
	}

	return 0;
}