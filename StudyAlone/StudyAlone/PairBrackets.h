#pragma once
#include<cstdio>

char stack[1000];
int top;
char str[1000], check[256];

int PairBrackets()
{
	check['>'] = '<';
	check[')'] = '(';
	check[']'] = '[';
	check['}'] = '{';

	for (int tc = 1; tc <= 10; tc++)
	{
		int len;
		scanf("%d\n%s\n", &len, str);
		top = 0;
		bool valid = true;

		for (int i = 0; i < len && valid; i++)
		{
			switch (str[i])
			{
			case '(':
			case'{':
			case'[':
			case'<':
				stack[top++]= str[i];
				break;
			case')':
			case'}':
			case']':
			case'>':

				//empty
				if (top == 0)
				{
					valid = false;
					break;
				}

				char t = stack[--top];
				if (t != check[str[i]]) valid = false;
				break;
			}
		}

		printf("#%d %d\n", tc, valid);
	}
	return 0;
}