//1889. 재영이는 기부천사 
//주소 : https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5L29NKD7sDFAXc&categoryId=AV5L29NKD7sDFAXc&categoryType=CODE&&&
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

char JaYeong_MAP[9][9];
bool JaYeong_info[3][9];
const int JaYeong_ROW = 0;
const int JaYeong_COL = 1;
const int JaYeong_VIL = 2;

int JaYeong_MAX(int x, int y)
{
	return x > y ?x : y;
}

int JaYeong_MAX(int x, int y,int z)
{
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

void Jayeong()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		int result = 0;
		memset(JaYeong_info, false, sizeof(JaYeong_info));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int viliagenum = (i / 3)*(3) + (j / 3);
				cin >> JaYeong_MAP[i][j];
				if (!(JaYeong_MAP[i][j]-'0')) continue;
				JaYeong_info[JaYeong_COL][j] = !JaYeong_info[JaYeong_COL][j];
				JaYeong_info[JaYeong_ROW][i] = !JaYeong_info[JaYeong_ROW][i];
				JaYeong_info[JaYeong_VIL][viliagenum] = !JaYeong_info[JaYeong_VIL][viliagenum];
			}
		}


		int num_of_value[3] = { 0,0,0 };
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (JaYeong_info[i][j])
				{
					num_of_value[i]++;
					result = JaYeong_MAX(result, num_of_value[i]);
				}
			}
		}
		cout << '#' << tc << ' ' << result << endl;
	}
}
