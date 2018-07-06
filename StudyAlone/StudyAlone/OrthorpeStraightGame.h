#pragma once
#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<cmath>
#include<time.h>
using namespace std;

map<pair<set<int>, int>, int > mp;
set<int> rlines, nlines;
set<pair<int, int> > chcod;
int cods[10001][2], clen;
int lines[1001][10001], llen[1001];

// 1 : ÀÌ±ט 0 : Áü
int winner( set<int>& nlines, int line)
{
	if (nlines.size() == 0)
	{
		return 1;
	}

	auto ret = mp.find({ rlines, line });
	if (ret != mp.end()) return ret->second;

	mp.insert(make_pair(make_pair(rlines, line), 1));
	ret = mp.find({ rlines, line });

	for (auto it = nlines.begin(); it != nlines.end(); it++)
	{
		set<int> next;
		rlines.insert(*it);

		for (int i = 0; i < llen[*it]; i++)
		{
			int x = cods[lines[*it][i]][0];
			int y = cods[lines[*it][i]][1] + 500;

			if (rlines.find(x) == rlines.end()) next.insert(x);
			if (rlines.find(y) == rlines.end()) next.insert(y);
		}

		int win = winner(next, *it);
	
		rlines.erase(*it);
		
		if (win == 1)
		{
			ret->second = 0;
			break;
		}
	}

	return ret->second;
}


int OrthopeStraightGame()
{
	int tc;
	///////////ran
	srand(time(NULL));
	///////////
	//scanf("%d\n", &tc);
	tc = 32;
	const char WIN[2] = { 'W','H' };

	for (int t = 1; t <= tc; t++)
	{
		//scanf("%d\n", &clen);
		clen = 800;
		memset(llen, 0, sizeof(llen));
		nlines.clear();
		rlines.clear();
		mp.clear();


		for (int i = 0; i < clen; i++)
		{
			int x, y;
			//scanf("%d %d\n", &x, &y);
			while (true)
			{
				x = rand() % 500 + 1;
				y = rand() % 500 + 1;
				if (chcod.find({ x,y }) == chcod.end())
				{
					chcod.insert({ x,y });
					break;
				}
			}

			cods[i][0] = x;
			cods[i][1] = y;

			lines[x][llen[x]++] = i;
			lines[y + 500][llen[y + 500]++] = i;

			nlines.insert(x);
			nlines.insert(y + 500);
		}
		int w = winner(nlines, 0);
		 printf("#%d %c\n", t, WIN[w]);
	}
	return 0;
}