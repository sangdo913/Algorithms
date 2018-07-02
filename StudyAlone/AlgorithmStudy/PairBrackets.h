#pragma once
#include<cstdio>

char stack[1000];
int top;

//ĳ���ʹ� 0~255 ���̱� ������ 256 ũ���� �迭�� �����ϸ� ��� ���ڿ� ���ؼ� ��ȯ�� ������ �� �ֽ��ϴ�.
char str[1000], check[256];

int PairBrackets()
{
	//������ȣ�� ������ȣ�� �񱳸� �ؾ��մϴ�. �̸� �迭�� �����صӴϴ�.
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

				//¦�� ���� �ʴ´�.
				if (t != check[str[i]]) valid = false;
				break;
			}
		}
		//������ ������� �ʴ�. (���� ��ȣ�� ����.)
		valid = top == 0;
		printf("#%d %d\n", tc, valid);
	}
	return 0;
}