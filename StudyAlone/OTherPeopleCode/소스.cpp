#include<cstdio>

int N, L, max, scr[21], k[21]; // ��᰹��, ���� Į�θ�, ���� �ִ�, ��Ằ ����, ��Ằ Į�θ�
void paohu(int n, int score, int kcal) // ����ȣ, ��������, Į�θ�����
{
	int i;
	if (kcal > L)return; // Į�θ����� > ���� Į�θ�
	if (n >= N) // ��������� ��� Ž��
	{
		max = max > score ? max : score; // ���� �ִ�, �������� ��
		return;
	}
	for (i = n + 1; i <= N; i++) // ��� �ߺ� �ȵǰ� i = n+1
	{
		paohu(i, score + scr[i], kcal + k[i]);
	}
}
int main()
{
	int T, l, i;
	scanf("%d", &T); // �׽�Ʈ ���̽�
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