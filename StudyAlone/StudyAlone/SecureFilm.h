#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
struct SecureFilm_Info
{
	typedef unsigned int ui;
	int d, w, k;
	bool map[25][25];
	bool storeMap[25][25];

	void init()
	{
		scanf("%d %d %d\n", &d, &w, &k);
		for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < w; j++)
				scanf("%d", &map[i][j]);
		}
	}
	int getZeroNum(int n)
	{
		if(n == 0) return -1;
		int res = 0;
		while(!(n & 1))
		{
			res ++;
			n >>= 1;
		}
		return res;
	}
	
	int getMin()
	{
		int num = k;

		for (int cnt = 0; cnt < k; cnt++)
		{
			int bit = (1 << cnt) - 1;

			while(bit < ( 1 << d))
			{
				int zeroNum = getZeroNum(bit);
				int temp = bit | (bit - 1);

				num = change(bit, false);
				num = num == -1 ? change(bit,true) : num;

				if (num != -1) return num;
				else if( zeroNum == -1) break;

				bit = (temp + 1) | (((~temp & -~temp) -1 ) >> (zeroNum + 1));
			}
		}

		return k;
	}

	int getBitNum( int n)
	{
		int cnt = 0;

		while (n)
		{
			if (n & 1) cnt++;
			n >>= 1;
		}
		return cnt;
	}

	int change( int selected, bool flag)
	{
		memcpy(storeMap, map, sizeof(map));
		int bitNum = getBitNum(selected);

		int depth = 0;
		while (selected)
		{
			if (selected & 1)
			{
				for (int i = 0; i < w; i++)
				{
					storeMap[depth][i] = flag;
				}
			}
			depth++;
			selected >>= 1;
		}
		if (check()) 
			return bitNum;

		return -1;
	}
	int change( int selected)
	{
		memcpy(storeMap, map, sizeof(map));
		int bitNum = getBitNum(selected);

		for ( int t = 0; t < (int)(( int)1 << bitNum); t++)
		{
			int temp = selected;
			int type = t;
			int depth = 0;
			while (temp)
			{
				if (temp & 1)
				{
					for (int i = 0; i < w; i++)
					{
						storeMap[depth][i] = type & 1;
					}
					type >>= 1;
				}
				depth++;
				temp >>= 1;
			}
			if (check()) 
				return bitNum;
		}

		return -1;
	}

	bool check()
	{
		int res = true;

		bool type;
		for (int j = 0; j < w; j++)
		{
			type = storeMap[0][j];
			int cnt = 1;
			bool ok = false;

			for (int i = 1; i < d; i++)
			{
				if (storeMap[i][j] == type)
				{
					cnt++;
				}
				else
				{
					cnt = 1;
					type = storeMap[i][j];
				}
				if (cnt == k)
				{
					ok = true;
					break;
				}
			}
			if (!ok) return false;
		}
		return true;
	}
}SecureFilm_info;

int SecureFilm()
{
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++)
	{
		SecureFilm_info.init();
		int res = SecureFilm_info.getMin();

		printf("#%d %d\n", tc, res);
	}
	return 0;
}