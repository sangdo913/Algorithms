#pragma once
//쿼드 트리 뒤집기
//알고스팟
//https://algospot.com/judge/problem/read/QUADTREE
#include<stdio.h>

enum datas {W = 'w', B = 'b', X = 'x'};

char str[1001];

struct QUAD
{
	QUAD* quads[4];
	char c;

	void print()
	{
		if (c == X)
		{
			printf("x");
			for (int i = 0; i < 4; i++)
			{
				quads[i]->print();
			}
		}
		else
		{
			printf("%c", c);
		}
	}
} ;

QUAD quads[1000];
int idx = 0;

QUAD* makeQuad(char* str, int &len)
{
	if (str[len] == X)
	{		
		len++;
		int p = idx++;
		quads[p].quads[0] = makeQuad(str, len);
		quads[p].quads[1] = makeQuad(str, len);
		quads[p].quads[2] = makeQuad(str, len);
		quads[p].quads[3] = makeQuad(str, len);

		quads[p].c = X;

		return &quads[p];
	}

	else
	{
		quads[idx].c = str[len];
		len++;

		return &quads[idx++];
	}
}

void reverseQUAD(QUAD* quad)
{
	if (quad->c == X)
	{
		for (int i = 0; i < 4; i++)
		{
			reverseQUAD(quad->quads[i]);
		}

		QUAD *t1 = quad->quads[0], *t2 = quad->quads[1];
		quad->quads[0] = quad->quads[2];
		quad->quads[1] = quad->quads[3];
		quad->quads[2] = t1;
		quad->quads[3] = t2;
	}
}

int QUADTREE()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		scanf("%s\n", str);
		idx = 0;
		
		QUAD* res;
		int len = 0;

		res = makeQuad(str, len);

		reverseQUAD(res);

		res->print();
		printf("\n");
	}

	return 0;
}