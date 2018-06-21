#pragma once
#include<cstdio>

long long morse[101][101], n, m;
long long k;


int MORSE()
{
	int t;
	const char c[2] = { 'o', '-' };

	char res[201] = { 0 };

	for (int i = 0; i < 101; i++)
	{
		morse[i][0] = morse[0][i] = 1;
	}

	for (int i = 1; i < 101; i++)
	{
		for (int j = 1; j < 101; j++)
		{
			//���� �÷ο� ����
			morse[i][j] = (morse[i - 1][j] + morse[i][j - 1]) > 1000000000000 ? 1000000000000 : (morse[i - 1][j] + morse[i][j - 1]);
		}
	}

	scanf("%d\n", &t);

	while (t--)
	{
		scanf("%lld %lld %lld\n", &n, &m, &k);
		int idx = n + m;
	
		for (int i = 0; i < idx; i++)
		{
			// ������ ���� �ʾ���.
			if (n == 0)
			{
				res[i] = 'o';
			}
			//�� ���� ����
			else if (k > morse[n-1][m])
			{
				k -= morse[n-1][m];
				m--;
				res[i] = c[0];
			}
			//�� ���� ����
			else
			{
				n--;
				res[i] = c[1];
			}
		}
		res[idx] = 0;
		printf("%s\n", res);
	}
	return 0;
}