#include <stdio.h>
#pragma warning (disable : 4996)

int N, M;
int map[10 + 1][10 + 1];
int visit[2][10 + 1][10 + 1];

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

typedef struct {
	int x;
	int y;
	int bri;
	int t;
}Queue;

Queue queue[100 * 100 * 100];

int wp, rp;
int enqueue(int x, int y, int t, int bri)
{
	queue[wp].x = x;
	queue[wp].y = y;
	queue[wp].t = t;
	queue[wp++].bri = bri;
	return 1;
}

int dequeue(Queue *t)
{
	if (rp == wp) return 0;

	*t = queue[rp++];

	return 1;
}

int bfs(void)
{
	int i;
	Queue t;
	int nx, ny;
	enqueue(0, 0, 0, 0);
	visit[0][0][0] = 1;

	while (dequeue(&t))
	{
		if (t.x == N - 1 && t.y == N - 1)
			return t.t;

		if (map[t.x][t.y] == 0) // 미리 올라간 다리위에 있을 때 예외 처리.
		{
			if (t.t%M != 0) // 다리위에가 주기 T가 되어야함. 0이아니면 대기.
			{
				enqueue(t.x, t.y, t.t + 1, t.bri);
				continue;
			}
		}

		if (map[t.x][t.y] > 1) // 미리 올라간 다리위에 있을 때 예외 처리.
		{
			if (t.t%map[t.x][t.y] != 0) // 다리위에가 주기 T가 되어야함. 0이 아니면 대기.
			{
				enqueue(t.x, t.y, t.t + 1, t.bri);
				continue;
			}
		}

		for (i = 0; i < 4; i++) //일반적인 이동
		{
			nx = t.x + dx[i]; ny = t.y + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N && map[nx][ny] != -1)
			{
				if (map[t.x][t.y] > 1 || map[t.x][t.y] == 0) //다리위에 있을 때
				{
					if (map[nx][ny] == 1 && visit[t.bri][nx][ny] == 0) // 다음 위치가 땅인 것만 고려하고 continue
					{
						visit[t.bri][nx][ny] = 1;
						enqueue(nx, ny, t.t + 1, t.bri);
					}
					continue;
				}

				if (map[nx][ny] == 1 && visit[t.bri][nx][ny] == 0) // 일반 땅
				{
					visit[t.bri][nx][ny] = 1;
					enqueue(nx, ny, t.t + 1, t.bri);
				}

				if (map[nx][ny] == 0 && t.bri <1 && visit[t.bri + 1][nx][ny] == 0) // 절벽 & 다리 한개 만들 수 있음. 일단 올려둔다.
				{
					visit[t.bri + 1][nx][ny] = 1;
					enqueue(nx, ny, t.t + 1, t.bri + 1);
				}

				if (map[nx][ny] > 1 && visit[t.bri][nx][ny] == 0) // 주어진 오작교
				{
					if (map[t.x][t.y] != 0 && map[t.x][t.y] > 1) // 현재 다리위에 있지 않으면 건넌다.
					{
						visit[t.bri][nx][ny] = 1;
						enqueue(nx, ny, t.t + 1, t.bri);
					}
				}
			}
		}
	}

	return 0;
}

void impossible(void)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 0)
			{
				if (i + 1 < N && j - 1 >= 0 && map[i + 1][j] == 0 && map[i][j - 1] == 0)
				{
					enqueue(i, j, 0, 0);
					continue;
				}
				if (j - 1 >= 0 && i - 1 >= 0 && map[i][j - 1] == 0 && map[i - 1][j] == 0)
				{
					enqueue(i, j, 0, 0);
					continue;
				}
				if (i - 1 >= 0 && j + 1 < N && map[i - 1][j] == 0 && map[i][j + 1] == 0)
				{
					enqueue(i, j, 0, 0);
					continue;
				}
				if (j + 1 < N && i + 1 < N && map[i][j + 1] == 0 && map[i + 1][j] == 0)
				{
					enqueue(i, j, 0, 0);
					continue;
				}
			}
		}

	Queue t;

	while (dequeue(&t))
	{
		map[t.x][t.y] = -1;
	}

	wp = rp = 0;
}

int main(void)
{
	int i, j;
	int T, t;
	scanf("%d", &T);

	for (t = 1; t <= T; t++)
	{
		scanf("%d %d", &N, &M);

		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				scanf("%d", &map[i][j]);


		impossible();

		int sol = bfs();

		printf("#%d %d\n", t, sol);

		wp = rp = 0;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					visit[i][j][k] = 0;

	}
	return 0;
}