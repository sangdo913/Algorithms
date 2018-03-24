#pragma once
#include<iostream>

using namespace std;

long long comb[2501][2501] = { 1 };
int HyeJung_Paint()
{
	int T, R, C, K;
	scanf("%d", &T);
	long long result;

	for (int i = 1; i < 2501; i++)
	{
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < 2501; j++)
		{
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % 1000000007;
		}
	}

	for (int tc = 1; tc <= T; tc++)
	{
		result = 0;
		scanf("%d %d %d", &R, &C, &K);
		int size = R*C;
		int nextSize;
		long long whiteOne, whiteTwo, whiteThree, whiteAll;
		if (R == 1 && C == 1)
		{
			result = K;
		}
		else if (R == 2 && C == 2)
		{
			switch (K)
			{
			case 1: result = 0; break;
			case 2: result = 2; break;
			case 3: result = 4; break;
			case 4: result = 1; break;
			}
		}

		else if (R == 1 || C == 1)
		{
			whiteOne = K < size ? comb[size - 1][K] << 1 : 0;
			whiteOne %= 1000000007;
			whiteTwo = K < size - 1 ? comb[size - 2][K] : 0;
			result = comb[size][K] + 1000000007 - whiteOne + whiteTwo;
			result %= 1000000007;
		}
		else
		{
			//1군데 화이트들 (상하좌우) - 2군데 화이트들(상하, 상좌, 상우, 하좌, 하우, 좌우) + 3군데 화이트들(상하좌, 하좌우) - 4군데 화이트들(상하좌우)
			whiteOne = K <= size - R ? comb[size - R][K] : 0;

			whiteOne += K <= size - C ? comb[size - C][K] : 0;

			whiteOne <<= 1;
			whiteOne %= 1000000007;

			whiteTwo = K <= size - R - C + 1 ? comb[size - R - C + 1][K] : 0;
			whiteTwo <<= 2;

			nextSize = size - 2 * R;
			whiteTwo += K <= nextSize ? comb[nextSize][K] : 0;

			nextSize = size - 2 * C;
			whiteTwo += K <= nextSize ? comb[nextSize][K] : 0;
			whiteTwo %= 1000000007;

			nextSize = size - R - C * 2 + 2;
			whiteThree = K <= size - R - C * 2 + 2 ? comb[nextSize][K] : 0;

			nextSize = size - R * 2 - C + 2;
			whiteThree += K <= nextSize ? comb[nextSize][K] : 0;
			whiteThree <<= 1;
			whiteThree %= 1000000007;

			nextSize = size - 2 * R - 2 * C + 4;
			whiteAll = K <= nextSize ? comb[nextSize][K] : 0;
			whiteAll %= 1000000007;

			//나머지 연산자의 특성 때문에 result가 음수가 나올 수 있다.
			long long sum = whiteOne + (1000000007 << 1) - whiteTwo + whiteThree - whiteAll;
			sum %= 1000000007;


			result = comb[size][K] + 1000000007 - sum;
			result %= 1000000007;
		}
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}