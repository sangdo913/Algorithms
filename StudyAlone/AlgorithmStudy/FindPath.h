#pragma once
#include<cstdio>
#include<cstring>

//adj[A][2] : A ���� ������ ����� ��ȣ�Դϴ�.
//������ ��尡 �ִ� 2���� �߱� ������ 2���� ������ ����ϴ�.

//alen[A] : A ���� ������ ����� ���� �Դϴ�.
//������ ��尡 �ִ� 2���̱� ������ alen���� 0, 1, 2 ������ �� �� �ϳ��� ���� �����ϴ�.

//visit : �湮�ߴ��� üũ�մϴ�.
//�׽�Ʈ ���̽� ��ȣ�� �־������, visit �迭�� �׽�Ʈ ���̽����� �ʱ�ȭ�� �ʿ䰡 �������ϴ�.
int queue[200], adj[100][2], visit[100] = { 0 }, alen[100] = { 0 };
int fr, re;

int FindPath()
{
	for (int tc = 1; tc <= 10; tc++)
	{
		int tn, n;

		memset(alen, 0, sizeof(alen));

		scanf("%d %d\n", &tn, &n);

		while (n--)
		{
			int from, to;
			scanf("%d %d \n", &from, &to);
			adj[from][alen[from]++] = to;
		}

		re = fr = 0;

		//ť�� ��� 0��(������)�� �ֽ��ϴ�.
		queue[re++] = 0;
		visit[0] = tc;

		bool isEnd = false;
		
		//ť�� �������� �����մϴ�.
		//ť�� ��� 0���� �˴ϴ�.
		while (re != fr)
		{
			int now = queue[fr++];

			//������ �� �ֽ��ϴ�!
			if (now == 99)
			{
				isEnd = true;
				break;
			}

			for (int i = 0; i < alen[now]; i++)
			{
				int next = adj[now][i];

				//�̹� �湮������ ť�� ���� �ʿ䰡 �����ϴ�.
				if (visit[next] == tc) continue;
				visit[next] = tc;

				// ���� ��带 �ֽ��ϴ�.
				queue[re++] = next;
			}
		}

		printf("#%d %d\n", tc, isEnd);
	}
	return 0;
}