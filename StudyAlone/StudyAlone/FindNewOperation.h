#pragma once
#include<iostream>
using namespace std;
struct _COD
{
	int x;
	int y;
};
unsigned int _arr[500][500];
_COD _arr2[50001];
int Find_New_Operation()
{
	int y_count = 1;
	int x = 1, y = 1;
	for (int cnt = 1; cnt <= 50000; cnt++)
	{
		_arr[y][x] = cnt;
		_arr2[cnt] = { x,y };
		x++; y--;
		if (y == 0)
		{
			x = 1; y = ++y_count;
		}
	}

	typedef int(*GetValue)(int x, int y);
	GetValue func = [](int x, int y)->int
	{
		_COD cod_x = _arr2[x]; _COD cod_y = _arr2[y];
		return _arr[cod_x.y + cod_y.y][cod_y.x + cod_x.x];
	};

	int T, p, q;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> p >> q;
		int  result = func(p, q);
		cout << '#' << tc << ' ' << result << endl;
	}
	return 0;
}
