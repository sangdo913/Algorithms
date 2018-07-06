#pragma once
#include<cstdio>
char map[8][9];

int PELINDROME()
{
	int t = 10;

	for (int tc = 1; tc <= t; tc++)
	{
		int n;
		scanf("%d\n", &n);

		int res = 0;
		for (int i = 0; i < 8; i++) {
			scanf("%s\n", map[i]);
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
			{
				bool isOK = true;

				if (i + n <= 8) {
					for (int k = 0; k < n / 2; k++)
					{
						if (map[i + k][j] != map[i + n - k - 1][j]) {
							isOK = false;
							break;
						}
					}

					res += isOK;
				}

				isOK = true;
				if (j + n <= 8) {
					for (int k = 0; k < n / 2; k++)
					{
						if (map[i][j + k] != map[i][j + n - k - 1]) {
							isOK = false;
							break;
						}
					}

					res += isOK;
				}
			}
		}

		printf("#%d %d\n", tc, res);
	}
	return 0;
}