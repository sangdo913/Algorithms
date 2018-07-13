#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define MAX(a, b) ((a > b) ? a : b)

int tc, N = 0;
int arrCnt[100001] = {};

long long Logic()
{
	long long sum = 0;

	// Set arrCnt
	int tmp, max = 0;
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &tmp);
		arrCnt[tmp]++;
		// Set Sum
		sum += tmp;
		// Set Max
		max = MAX(tmp, max);
	}

	// Logic
	int cnt = 0;
	for (int i = max; i > 0; --i)
	{
		if (cnt == N)	break;
		if (arrCnt[i] == 0)	continue;

		tmp = ((arrCnt[i] + cnt) / 3) - (cnt / 3);

		sum -= ((long long)i * tmp);
		cnt += arrCnt[i];
	}

	return sum;
}

int main()
{

	int T;
	scanf("%d", &T);

	for (tc = 1; tc <= T; ++tc)
	{
		for (int i = 0; i < N; ++i)
			arrCnt[i] = 0;
		scanf("%d", &N);
		printf("#%d %lld\n", tc, Logic());
	}
}