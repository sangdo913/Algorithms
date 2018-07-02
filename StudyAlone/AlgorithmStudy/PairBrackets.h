#pragma once
#include<cstdio>

char stack[1000];
int top;

//캐릭터는 0~255 값이기 때문에 256 크기의 배열을 선언하면 모든 문자에 대해서 변환을 수행할 수 있습니다.
char str[1000], check[256];

int PairBrackets()
{
	//닫힘괄호는 열린괄호와 비교를 해야합니다. 이를 배열에 저장해둡니다.
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

				//짝이 맞지 않는다.
				if (t != check[str[i]]) valid = false;
				break;
			}
		}
		//스택이 비어있지 않다. (열린 괄호가 많다.)
		valid = top == 0;
		printf("#%d %d\n", tc, valid);
	}
	return 0;
}