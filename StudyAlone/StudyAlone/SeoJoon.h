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

		//�ʱ�ȭ
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
		//0�� �ƴ� ���� �ε���
		for (zero_index = N - 1; SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0; zero_index-- );

		// ���������� �ٸ��� �ȵ�
		if (sum[0] == sum[1])
		{
			for (int i = 0; i < N &&SeoJoon_puzzle[SEOJOON_ROW][i] > 0; i++)
			{
				//0 �ٷ� ���� ����Ű���� ����
				while (SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0 && zero_index >= 0) zero_index--;
				//���� �ε����� 0�̰� �� ���� 0 �̸� ����� ����
				if (SeoJoon_puzzle[SEOJOON_COL][zero_index] == 0)
				{
					flag = true;
					break;
				}

				int hint = SeoJoon_puzzle[SEOJOON_ROW][i];
				//�ٸ� ������ �� �ε����� �����Ѵٸ� ������ ���� �� ���� �� �ִ�.
				flag |= zero_index - hint >= 0;
				// ��� ���� ��带 �����Ѵ�.
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

		// ������ �ٸ��� NO ǥ��
		else
		{
			flag = true;
		}
		cout << "#"<<t<< " " << result[flag] << endl;
	}
}