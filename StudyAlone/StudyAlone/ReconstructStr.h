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
			//��Ī(Ȧ��)
			if (rs == le)
			{
				res[rLen++] = str[r--];
				le = l;
				rs = r;

				//1 ������
				if (r == l)
				{
					res[rLen++] = str[r];
				}

				continue;
			}
			//��Ī(¦��)
			else if (rs < le)
			{
				res[rLen++] = str[l++];

				le = l;
				rs = r;

				continue;
			}

			//������ ����
			if (str[le] > str[l] && str[rs] > str[r])
			{
				res[rLen++] = str[l++];

				rs = r;
				le = l;

				continue;
			}

			// ������ �����ų� ����
			else if (str[le] <= str[l] && str[rs] <= str[r])
			{
				//�ű�� ��Ī
				if (str[le] == str[rs])
				{
					le++; rs--;

					continue;
				}
			}

			// ���Ī
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