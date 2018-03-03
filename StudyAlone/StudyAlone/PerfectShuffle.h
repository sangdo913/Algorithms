#pragma once
#include<iostream>

using namespace std;

int Shuffle_deck[1000];
char Shuffle_cards[1000][81];

int PerfectShuffle()
{
	ios::ios_base::sync_with_stdio(false);
	int T,N;
	cin >> T;
	int left; int right;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		for (int i = 0; i<N;i++)
			cin >> Shuffle_cards[i];
		
		left = 0;
		right = (N+1) >> 1;

		for (int i = 0; i < N; i++)
		{
			if (!(i & 1))
			{
				Shuffle_deck[i] = left++;
			}
			else
			{
				Shuffle_deck[i] = right++;
			}
		}
		cout << '#' << tc << ' ';
		for (int i = 0; i < N; i++)
		{
			cout << Shuffle_cards[Shuffle_deck[i]] << ' ';
		}
		cout << '\n';
	}
	return 0;
}