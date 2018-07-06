#include<cstdio>

long long factorial[40];
long long numOfPair[26][5], num, makeNum[26];
int len;

int JaYeongFactorial()
{
	factorial[0] = 1;
	for (len = 1; len < 40; len++)
	{
		if (factorial[len - 1] * 5 > (long long)(1e18)) break;
		factorial[len] = factorial[len-1] * 5;
	}

	numOfPair[0][0] = 1;
	numOfPair[0][1] = 2;
	numOfPair[0][2] = 3;
	numOfPair[0][3] = 4;
	numOfPair[0][4] = 5;

	for (int i = 1; i < len; i++)
	{
		for(int j = 0; j < i; j++)
			numOfPair[i][1] += numOfPair[j][4];

		for (int j = 2; j < 5; j++)
		{
			//5 진수의 i 번째가 홀수면 다음 수때 반전이 시작됨 (홀수 -> 짝수, 짝수 -> 홀수)
			if (i & 1)
			{
				//j 가 또 홀수이면 반전에 반전이므로 원래 값이 됨 (홀수 -> 홀수, 짝수 -> 홀수)
				numOfPair[i][j] = j & 1 ? numOfPair[i][j - 1] + numOfPair[i][1] : numOfPair[i][j - 1] + factorial[i] - numOfPair[i][1];
			}
			//5 진수의 i 번째 자리수가 짝수이면 그대로 더해주면됨.
			else
			{
				numOfPair[i][j] = numOfPair[i][j - 1] + numOfPair[i][1];
			}
		}
	}

	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		
			scanf("%lld\n", &num);
			long long res = 0;

			bool isPair = true;
			//5 진수 만들기
			for (int i = 25; i >= 0; i--)
			{	
				makeNum[i] = num / factorial[i];
				num = num % factorial[i];

				//짝수의 경우 numOfPair를 그대로 더하면 됨.
				if (isPair) res += numOfPair[i][makeNum[i]];

				//홀수의 경우 numOfPair를 반전해야함
				// numOfPair[0][0]이 1이기 때문에 0 보다 작아지는 경우가 있었음.
				else res += factorial[i] * makeNum[i] - numOfPair[i][makeNum[i]] > 0 ? factorial[i] * makeNum[i] - numOfPair[i][makeNum[i]] : 0;
				
				//짝수(1) ^ 반전(1) = 홀수(0)
				//홀수(0) ^ 반전(1) = 짝수(1)
				//짝수(1) ^ 반전X(0) = 짝수(1)
				//홀수(0) ^ 반전X(0) = 홀수(0)
				isPair ^= (i & 1) && (makeNum[i] & 1);
			}

			printf("#%d %lld\n", tc, res);
	}

	return 0;
}