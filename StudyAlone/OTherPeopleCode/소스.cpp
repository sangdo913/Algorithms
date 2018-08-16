//#include <iostream>
#include <stdio.h>
#include <string.h>
#define MX 10010
#define ABS(X) ((X) > 0 ? (X) : -(X))
#define MIN(X, Y) ((X) > (Y) ? (Y) : (X))
#define INF 987654321
//using namespace std;

char A[MX];
int dp[MX][7], visit[MX];
int C;

int check(int st, int ed)
{
	int flag = 0;
	for (int i = st; i < ed; i++)
	{
		if (A[i] != A[st]) { flag = 1; break; }
	}
	if (!flag) return 1;
	flag = 0;
	int d = A[st + 1] - A[st];
	
	flag = ABS(d) != 1;

	if (!flag) {
		for (int i = st + 1; i < ed; i++)
		{
			if (A[i] - A[i - 1] != d) { flag = 1; break; }
		}
	}

	if (!flag) return 2;
	flag = 0;
	for (int i = st + 2; i < ed; i++)
	{
		if (A[i] != A[i - 2]) { flag = 1; break; }
	}
	if (!flag) return 4;
	flag = 0;
	for (int i = st; i < ed - 1; i++)
	{
		if (A[st + 1] - A[st] != A[i + 1] - A[i]) { flag = 1; break; }
	}
	if (!flag) return 5;
	return 10;
}

int solve()
{
	visit[0] = 0;
	for (int i = 3; i <= strlen(A); i++)
	{
		for (int j = 3; j <= 5; j++)
		{
			if (i - j < 0) continue;
			visit[i] = MIN(visit[i], (visit[i - j] + dp[i - j][j]));
		}
	}
	return visit[strlen(A)];
}

int main(void)
{
	scanf("%d", &C);
	while (C--)
	{
		scanf("%s", A);
		for (int i = 0; i <= strlen(A); i++)
			visit[i] = 987654321;

		for (int i = 0; i < strlen(A); i++)
			for (int j = 3; j <= 5; j++)
				if (i + j <= strlen(A))
					dp[i][j] = check(i, i + j);

		printf("%d\n", solve());
	}
	return 0;
}