#pragma once
#include<cstdio>
#include<cstring>

char str[21];
const char rStr[2][10] = {  "Not exist","Exist"};

int pelindrome2()
{
	int t;
	scanf("%d\n", &t);

	for (int i = 1; i <= t; i++)
	{
		scanf("%s\n", str);
		int len = strlen(str);

		bool res = true;
		for (int i = 0; i < len / 2; i++)
		{
			if (str[i] == '*' || str[len - i - 1] == '*') break;
			if (res = str[i] == str[len - i - 1]) continue;
		}

		printf("#%d %s\n",i, rStr[res]);
	}
	return 0;
}