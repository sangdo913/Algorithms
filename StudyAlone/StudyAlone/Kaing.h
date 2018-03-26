#pragma once
#include<iostream>


using namespace std;

void Kaing()
{
	int K;
	int M, N,x,y,X,Y;
	cin >> K;
	for (int tc = K; tc--;)
	{
		cin >> M >> N >> X >> Y; 

		int larger;
		if (M < N)
		{
			larger = N;
			N = M;
			M = larger;
			
			larger = X;
			X = Y;
			Y = larger;
		}

		int GongBasu = M;
		int remain = N;
		int remainM = 0, remainN = 1, prevRM = 1, prevRN = 0;
		while (remain != 0)
		{
			int temp1 = remainM;
			remainM = prevRM - remainM*(GongBasu / remain);
			prevRM = temp1;

			temp1 = remainN;
			remainN = prevRN - remainN*(GongBasu / remain);
			prevRN = temp1;
			larger = GongBasu;
			GongBasu = remain;
			remain = larger % remain;
		}

		GongBasu = M*N / GongBasu;
		int cols = X;
		int cnt = x = X;
		
		Y = Y - X + 1;
		while (Y <= 0) Y += N;
		bool is_found = false;
		while (cnt <= GongBasu )
		{
			if (Y == 1)
			{
				is_found = true;
				break;
			}
			cnt += M;
			Y = (Y - M%N+N) % N;
			if (Y == 0) Y = N;
		}
		//bool is_find = false;
		//int j,i = j = 0;
		//for (; i*M < GongBasu && !is_find; i++)
		//{
		//	j = 0;
		//	for (; j*N < GongBasu; j++)
		//	{
		//		if (i*M + X == j*N + Y)
		//		{
		//			is_find = true;
		//			break;
		//		}

		//	}
		//}

		cout << (is_found ? cnt : -1) << endl;
	}
}