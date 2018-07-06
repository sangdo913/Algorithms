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
			//5 ������ i ��°�� Ȧ���� ���� ���� ������ ���۵� (Ȧ�� -> ¦��, ¦�� -> Ȧ��)
			if (i & 1)
			{
				//j �� �� Ȧ���̸� ������ �����̹Ƿ� ���� ���� �� (Ȧ�� -> Ȧ��, ¦�� -> Ȧ��)
				numOfPair[i][j] = j & 1 ? numOfPair[i][j - 1] + numOfPair[i][1] : numOfPair[i][j - 1] + factorial[i] - numOfPair[i][1];
			}
			//5 ������ i ��° �ڸ����� ¦���̸� �״�� �����ָ��.
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
			//5 ���� �����
			for (int i = 25; i >= 0; i--)
			{	
				makeNum[i] = num / factorial[i];
				num = num % factorial[i];

				//¦���� ��� numOfPair�� �״�� ���ϸ� ��.
				if (isPair) res += numOfPair[i][makeNum[i]];

				//Ȧ���� ��� numOfPair�� �����ؾ���
				// numOfPair[0][0]�� 1�̱� ������ 0 ���� �۾����� ��찡 �־���.
				else res += factorial[i] * makeNum[i] - numOfPair[i][makeNum[i]] > 0 ? factorial[i] * makeNum[i] - numOfPair[i][makeNum[i]] : 0;
				
				//¦��(1) ^ ����(1) = Ȧ��(0)
				//Ȧ��(0) ^ ����(1) = ¦��(1)
				//¦��(1) ^ ����X(0) = ¦��(1)
				//Ȧ��(0) ^ ����X(0) = Ȧ��(0)
				isPair ^= (i & 1) && (makeNum[i] & 1);
			}

			printf("#%d %lld\n", tc, res);
	}

	return 0;
}