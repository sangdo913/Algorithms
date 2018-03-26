#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define SEOJOON_MAX 1001
#define SEOJOON_YES 0
#define SEOJOON_NO 1
#define SEOJOON_ROW 0
#define SEOJOON_COL 1
using namespace std;
void SeoJoon()
{
	int SeoJoon_puzzle[2][SEOJOON_MAX];
	int T;
	char result[2][4] = { "Yes","No" };

	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		memset(SeoJoon_puzzle, 0, sizeof(SeoJoon_puzzle));
		bool flag = false, valid = true;
		int sum[2] = { 0,0 };
		int N,number;
		cin >> N;

		//초기화
		for (int rc = 0; rc < 2; rc++)
		{
			for (int i = 0; i < N; i++)
			{
				cin >> SeoJoon_puzzle[rc][i];
				sum[rc] += SeoJoon_puzzle[rc][i];
			}
			sort(SeoJoon_puzzle[rc], SeoJoon_puzzle[rc] + N, greater<int>());
		}

		int zero_index;
		//0이 아닌 곳의 인덱스
		for (zero_index = N - 1; SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0; zero_index-- );

		// 검은블럭수가 다르면 안됨
		if (sum[0] == sum[1])
		{
			for (int i = 0; i < N &&SeoJoon_puzzle[SEOJOON_ROW][i] > 0; i++)
			{
				//0 바로 전을 가르키도록 설정
				while (SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0 && zero_index >= 0) zero_index--;
				//만약 인덱스가 0이고 그 값이 0 이면 만들기 실패
				if (SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0)
				{
					flag = true;
					break;
				}

				int hint = SeoJoon_puzzle[SEOJOON_ROW][i];
				//다른 곳으로 갈 인덱스가 존재한다면 퍼즐을 여러 개 만들 수 있다.
				flag |= zero_index - hint >= 0;
				// 행과 열의 노드를 연결한다.
				for (int j = zero_index; j > zero_index - hint; j--)
				{
					if (j < 0)
					{
						flag = true; break;
					}
					--SeoJoon_puzzle[SEOJOON_COL][j];
				}
			}
		}

		// 블럭수가 다르면 NO 표시
		else
		{
			flag = true;
		}
		cout << "#"<<t<< " " << result[flag] << endl;
	}
}