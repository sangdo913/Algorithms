#pragma once
#include<cstdio>

int getSize(char* str)
{
	int i = 0;
	while (str[i])
	{
		++i;
	}
	return i;
}

bool check(char *str, int size)
{
	for (int i = 0; i < (size >> 1); i++)
	{
		if (str[i] == '?' || str[size - i - 1] == '?') continue;

		if (str[i] != str[size - 1 - i]) return false;
	}
	return true;
}

int GlobalPelindrome()
{
	int t;
	scanf("%d\n", &t);

	const char res[2][11] = { "Not exist", "Exist" };
	for (int tc = 1; tc <= t; tc++)
	{
		char str[21];

		scanf("%s\n", str);

		printf("#%d %s\n", tc, res[check(str, getSize(str))]);
	}

	return 0;
}