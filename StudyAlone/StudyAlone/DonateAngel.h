//1889. 재영이는 기부천사 
//주소 : https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5L29NKD7sDFAXc&categoryId=AV5L29NKD7sDFAXc&categoryType=CODE&&&
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

char JaYeong_MAP[9][9];
int JaYeong_Value = 81;
const int JaYeong_ROW = 1;
const int JaYeong_COL = 2;
const int JaYeong_VIL = 0;

int JaYeong_MAX(int x, int y)
{
	return x > y ?x : y;
}

int JaYeong_ARRMAX(bool JaYeong_info[3][9])
{
	int result = 0;
	int num_of_value[3] = { 0,0,0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (JaYeong_info[i][j])
			{
				num_of_value[i]++;
			}
		}
		result = JaYeong_MAX(result, num_of_value[i]);
	}

	return result;
}

void JaYeong_Check(bool infoes[3][9], int what,int n)
{
	int vilage, col, row;
	bool isCheck = false;
	switch (what)
	{
	case JaYeong_COL:
		col = n;
		row = 0;
		vilage = n / 3;
		break;
	case JaYeong_ROW:
		row = n;
		for (int i = 0; i < 9 ; i++)
		{
			if (!infoes[JaYeong_COL][i]) continue;
			isCheck = true;
			col = i;
			break;
		}
		if (isCheck)
		{
			vilage = (n / 3) * 3 + col / 3;
		}
		else
		{
			col = 0;
			vilage = (n / 3)*3;
		}
		break;
	case JaYeong_VIL :
		vilage = n;
		row = (n/3)*3;
		col = (n % 3)*3;
		for (int i = 0; i < 3; i++)
		{
			if (!infoes[JaYeong_ROW][row + i]) continue;
			row = row + i;
			break;
		}
		for (int i = 0; i < 3; i++)
		{
			if (!infoes[JaYeong_COL][col + i]) continue;
			col = col + i;
			break;
		}
		break;
	}

	infoes[JaYeong_VIL][vilage] = !infoes[JaYeong_VIL][vilage];
	infoes[JaYeong_ROW][row] = !infoes[JaYeong_ROW][row];
	infoes[JaYeong_COL][col] = !infoes[JaYeong_COL][col];
}

int JaYeong_Get(char JaYeong_MAP[9][9])
{
	bool infoes[3][9];
	int count = 0;
	memset(infoes, false, sizeof(infoes));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int viliagenum = (i / 3)*(3) + (j / 3);

			if (!(JaYeong_MAP[i][j] == '1' || JaYeong_MAP[i][j] == '0')) continue;
			if (!(JaYeong_MAP[i][j] - '0')) continue;
			infoes[JaYeong_COL][j] = !infoes[JaYeong_COL][j];
			infoes[JaYeong_ROW][i] = !infoes[JaYeong_ROW][i];
			infoes[JaYeong_VIL][viliagenum] = !infoes[JaYeong_VIL][viliagenum];
		}
	}
	while (JaYeong_ARRMAX(infoes) > 0)
	{
		count++;
		bool check = false;
		for (int i = 0; i < 3&& !check; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (!infoes[i][j]) continue;
				JaYeong_Check(infoes, i, j);
				check = true;
				break;
			}
		}

	}
	return count;
}

void Jayeong()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		int result = 0 ;
		for (int i = 0; i < 9;i++)
		for (int j = 0; j < 9; j++)
		{
			cin >> JaYeong_MAP[i][j];
		}
		result = JaYeong_Get(JaYeong_MAP);


		cout << '#' << tc << ' ' << result << endl; 
	}
}
