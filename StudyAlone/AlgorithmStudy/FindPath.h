#pragma once
#include<cstdio>
#include<cstring>

//adj[A][2] : A 노드와 인접한 노드의 번호입니다.
//인접한 노드가 최대 2개라 했기 때문에 2개의 공간만 만듭니다.

//alen[A] : A 노드와 인접한 노드의 개수 입니다.
//인접한 노드가 최대 2개이기 때문에 alen에는 0, 1, 2 세개의 값 중 하나의 값을 가집니다.

//visit : 방문했는지 체크합니다.
//테스트 케이스 번호를 넣어놓으면, visit 배열을 테스트 케이스마다 초기화할 필요가 없어집니다.
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

		//큐에 노드 0번(시작점)을 넣습니다.
		queue[re++] = 0;
		visit[0] = tc;

		bool isEnd = false;
		
		//큐가 빌때까지 실행합니다.
		//큐가 비면 0값이 됩니다.
		while (re != fr)
		{
			int now = queue[fr++];

			//도착할 수 있습니다!
			if (now == 99)
			{
				isEnd = true;
				break;
			}

			for (int i = 0; i < alen[now]; i++)
			{
				int next = adj[now][i];

				//이미 방문했으면 큐에 넣을 필요가 없습니다.
				if (visit[next] == tc) continue;
				visit[next] = tc;

				// 다음 노드를 넣습니다.
				queue[re++] = next;
			}
		}

		printf("#%d %d\n", tc, isEnd);
	}
	return 0;
}