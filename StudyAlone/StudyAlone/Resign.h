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

//가능한 모든 선택 가능 날짜 탐색
int Resign_Value(int index, int size, int value)
{
	if (index >= size) return value;
	int ret = value;
	for (int i = index + Resign_Counsel[ResignT][index]-1; i < size; i++)
	{
		//상담이 가능한 날짜는 T에 써있는 날짜를 더한 순간 부터 이다.
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
		//오늘 예정된 상담이 퇴사 전에 끝난다면, 전날의 수익 최댓값과 오늘 하는 상담의 수익을 더하고, 상담이 끝난 날의 수익과 비교해서 최댓값을 갱신한다.
		counsel_dp[i + Resign_Counsel[ResignT][i] - 1] = i + Resign_Counsel[ResignT][i] - 1 <= N? Resign_MAX(counsel_dp[i + Resign_Counsel[ResignT][i] - 1], counsel_dp[i - 1] + Resign_Counsel[ResignP][i])
			: counsel_dp[i + Resign_Counsel[ResignT][i] - 1];
		//어제의 상담의 최댓값과 오늘의 상담 중 큰 값을 넣는다.
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

	////시작 날짜를 0부터 N-1까지로 한다.
	//for (int i = 0; i < N; i++)
	//	result = Resign_MAX(result,Resign_Value(i,N,0));
	result = Resign_Value_DP(N);


	
	cout << result << endl;
}