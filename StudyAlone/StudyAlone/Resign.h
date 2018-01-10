#pragma once
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;
int Resign_Counsel[2][16];
const int T = 0;
const int P = 1;
int Resign_MAX(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

//������ ��� ���� ���� ��¥ Ž��
int Resign_Value(int index, int size, int value)
{
	if (index >= size) return value;
	int ret = value;
	for (int i = index + Resign_Counsel[T][index]-1; i < size; i++)
	{
		//����� ������ ��¥�� T�� ���ִ� ��¥�� ���� ���� ���� �̴�.
		ret = Resign_MAX(ret, Resign_Value(i+1, size, value + Resign_Counsel[P][index]));
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
		counsel_dp[i + Resign_Counsel[T][i] - 1] = i + Resign_Counsel[T][i] - 1 <= N? Resign_MAX(counsel_dp[i + Resign_Counsel[T][i] - 1], counsel_dp[i - 1] + Resign_Counsel[P][i])
			: counsel_dp[i + Resign_Counsel[T][i] - 1];	
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
		cin >> Resign_Counsel[T][i] >> Resign_Counsel[P][i];
	}

	////���� ��¥�� 0���� N-1������ �Ѵ�.
	//for (int i = 0; i < N; i++)
	//	result = Resign_MAX(result,Resign_Value(i,N,0));
	result = Resign_Value_DP(N);


	
	cout << result << endl;
}