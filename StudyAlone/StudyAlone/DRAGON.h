#pragma once
#include<cstdio>
#include<cstring>

char res[55]; // ��� ����
const char type[4][4] = { "+FX", "-FX", "+YF", "-YF"}; //���� Ÿ���� 4 ���� ���´�.
const int conv[4][2] = { {0,2}, {1,2}, {0,3}, {1,3} }; //�θ� ���ڷκ��� ������� �� �ִ� ���ڵ�

int memoi[51][20];

int st[51]; // �޸������̼ǿ��� ���� �Ǵ� ������ ��ġ

void getGen(int gen, int p)
{
	int &ret = memoi[gen][p - st[gen]];
	
	if (ret != -1)
	{
		return;
	}

	//�θ� ���� ���ڸ� �˾Ƴ���.
	getGen(gen - 1, p / 2);

	//�θ� ����κ��� ��������� 2 ���� ���ڵ�
	int *change = (int*)conv[memoi[gen - 1][p / 2 - st[gen-1]]];

	//�ϳ��ۿ� ��ä��
	if (p % 2)
	{
		ret = change[1];

	}
	//�ΰ� �� ä�� �� ����
	else
	{
		ret = change[0];
		memoi[gen][p - st[gen] + 1] = change[1];
	}
}

int DRAGON()
{
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		memset(memoi, -1, sizeof(memoi));

		memoi[0][0] = 0; // ù ��° ���� ���ڴ� +FX

		int gen, p, l;

		scanf("%d %d %d\n", &gen, &p, &l);

		st[gen] = p / 3; //ù��° ������ ���� ��ġ

		//ù ��° ������ ��ġ�� ���� �θ� ������� ���� ���� ��ġ�� �� �� �ִ�.
		for (int i = gen - 1; i >= 0; i--)
		{
			st[i] =  st[i+1] / 2;
		}

		//���ڸ� ã�´�.
		for (int i = 0; i < l / 3 + 2; i++)
		{
			if (memoi[gen][i] == -1) getGen(gen, st[gen] + i);
		}

		int len = 0;

		//ã�� ���ڸ� �������� ������� ä���.
		for (int i = 0; i < l / 3 + 2; i++)
		{
			res[len++] = type[memoi[gen][i]][0];
			res[len++] = type[memoi[gen][i]][1];
			res[len++] = type[memoi[gen][i]][2];
		}
		res[l + p % 3] = 0;

		printf("%s\n", res + p % 3);
	}
	return 0;
}