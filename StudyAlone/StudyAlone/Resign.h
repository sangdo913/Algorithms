#pragma once
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;
int Resign_Counsel[2][16];
const int ResignT = 0;
const int ResignP = 1;
int Resign_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

//������ ��� ���� ���� ��¥ Ž��
int Resign_Value(int index, int size, int value)
{
	if (index >= size) return value;
	int ret = value;
	for (int i = index + Resign_Counsel[ResignT][index]-1; i < size; i++)
	{
		//����� ������ ��¥�� T�� ���ִ� ��¥�� ���� ���� ���� �̴�.
		ret = Resign_MAX(ret, Resign_Value(i+1, size, value + Resign_Counsel[ResignP][index]));
	}
	return ret;
}

int Resign_Value_DP(int N)
{
	int counsel_dp[16];
	memset(counsel_dp, 0, sizeof(counsel_dp));
	for (int i = 1; i <= N; i++)
	{
		//���� ������ ����� ��� ���� �����ٸ�, ������ ���� �ִ񰪰� ���� �ϴ� ����� ������ ���ϰ�, ����� ���� ���� ���Ͱ� ���ؼ� �ִ��� �����Ѵ�.
		counsel_dp[i + Resign_Counsel[ResignT][i] - 1] = i + Resign_Counsel[ResignT][i] - 1 <= N? Resign_MAX(counsel_dp[i + Resign_Counsel[ResignT][i] - 1], counsel_dp[i - 1] + Resign_Counsel[ResignP][i])
			: counsel_dp[i + Resign_Counsel[ResignT][i] - 1];
		//������ ����� �ִ񰪰� ������ ��� �� ū ���� �ִ´�.
		counsel_dp[i] = Resign_MAX(counsel_dp[i], counsel_dp[i - 1]);
	}

	return counsel_dp[N];
}

void Resign()
{
	int N;
	cin >> N;
	int Counsel = 0, result = 0;

	for (int i = 1; i <= N; i++)
	{
		cin >> Resign_Counsel[ResignT][i] >> Resign_Counsel[ResignP][i];
	}

	////���� ��¥�� 0���� N-1������ �Ѵ�.
	//for (int i = 0; i < N; i++)
	//	result = Resign_MAX(result,Resign_Value(i,N,0));
	result = Resign_Value_DP(N);


	
	cout << result << endl;
}