#include<cstdio>

int N, L, max, scr[21], k[21]; // 재료갯수, 제한 칼로리, 점수 최댓값, 재료별 점수, 재료별 칼로리
void paohu(int n, int score, int kcal) // 재료번호, 점수총합, 칼로리총합
{
	int i;
	if (kcal > L)return; // 칼로리총합 > 제한 칼로리
	if (n >= N) // 모든종류의 재료 탐색
	{
		max = max > score ? max : score; // 점수 최댓값, 점수총합 비교
		return;
	}
	for (i = n + 1; i <= N; i++) // 재료 중복 안되게 i = n+1
	{
		paohu(i, score + scr[i], kcal + k[i]);
	}
}
int main()
{
	int T, l, i;
	scanf("%d", &T); // 테스트 케이스
	for (l = 1; l <= T; l++)
	{
		max = 0;
		scanf("%d%d", &N, &L);
		for (i = 1; i <= N; i++)
			scanf("%d%d", &scr[i], &k[i]);
		paohu(0, 0, 0);
		printf("#%d %d\n", l, max);
	}
}