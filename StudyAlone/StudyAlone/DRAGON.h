#pragma once
#include<cstdio>
#include<cstring>

char res[55]; // 결과 저장
const char type[4][4] = { "+FX", "-FX", "+YF", "-YF"}; //글자 타입은 4 개가 나온다.
const int conv[4][2] = { {0,2}, {1,2}, {0,3}, {1,3} }; //부모 글자로부터 만들어질 수 있는 글자들

int memoi[51][20];

int st[51]; // 메모이제이션에서 시작 되는 글자의 위치

void getGen(int gen, int p)
{
	int &ret = memoi[gen][p - st[gen]];
	
	if (ret != -1)
	{
		return;
	}

	//부모 세대 글자를 알아낸다.
	getGen(gen - 1, p / 2);

	//부모 세대로부터 만들어지는 2 개의 글자들
	int *change = (int*)conv[memoi[gen - 1][p / 2 - st[gen-1]]];

	//하나밖에 못채움
	if (p % 2)
	{
		ret = change[1];

	}
	//두개 다 채울 수 있음
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

		memoi[0][0] = 0; // 첫 번째 세대 글자는 +FX

		int gen, p, l;

		scanf("%d %d %d\n", &gen, &p, &l);

		st[gen] = p / 3; //첫번째 글자의 시작 위치

		//첫 번째 글자의 위치로 부터 부모 세대들의 시작 글자 위치를 알 수 있다.
		for (int i = gen - 1; i >= 0; i--)
		{
			st[i] =  st[i+1] / 2;
		}

		//글자를 찾는다.
		for (int i = 0; i < l / 3 + 2; i++)
		{
			if (memoi[gen][i] == -1) getGen(gen, st[gen] + i);
		}

		int len = 0;

		//찾은 글자를 바탕으로 결과값을 채운다.
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