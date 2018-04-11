#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
struct SecureFilm_Info
{
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

	int getMin()
	{
		int num = k;

		for (int cnt = 0; cnt < k; cnt++)
			for ( int i = 0; i < (int)(( int)1 << d); i++)
			{
				if (cnt != getBitNum(i)) continue;	
				num = change(i);
				if (num != -1) return num;
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

		cout << '#' << tc << ' ' << res << endl;
	}
	return 0;
}