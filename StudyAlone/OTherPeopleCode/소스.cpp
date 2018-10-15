#include <iostream>
#include<cstring>

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

		if (map[t.x][t.y] == 0) // �̸� �ö� �ٸ����� ���� �� ���� ó��.
		{
			if (t.t%M != 0) // �ٸ������� �ֱ� T�� �Ǿ����. 0�̾ƴϸ� ���.
			{
				enqueue(t.x, t.y, t.t + 1, t.bri);
				continue;
			}
		}

		if (map[t.x][t.y] > 1) // �̸� �ö� �ٸ����� ���� �� ���� ó��.
		{
			if (t.t%map[t.x][t.y] != 0) // �ٸ������� �ֱ� T�� �Ǿ����. 0�� �ƴϸ� ���.
			{
				enqueue(t.x, t.y, t.t + 1, t.bri);
				continue;
			}
		}

		for (i = 0; i < 4; i++) //�Ϲ����� �̵�
		{
			nx = t.x + dx[i]; ny = t.y + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N)
			{
				if (map[t.x][t.y] > 1 || map[t.x][t.y] == 0) //�ٸ����� ���� ��
				{
					if (map[nx][ny] == 1 && visit[t.bri][nx][ny] == 0) // ���� ��ġ�� ���� �͸� ����ϰ� continue
					{
						visit[t.bri][nx][ny] = 1;
						enqueue(nx, ny, t.t + 1, t.bri);
					}
					continue;
				}

				if (map[nx][ny] == 1 && visit[t.bri][nx][ny] == 0) // �Ϲ� ��
				{
					visit[t.bri][nx][ny] = 1;
					enqueue(nx, ny, t.t + 1, t.bri);
				}

				if (map[nx][ny] == 0 && t.bri <1 && visit[t.bri + 1][nx][ny] == 0) // ���� & �ٸ� �Ѱ� ���� �� ����. �ϴ� �÷��д�.
				{
					visit[t.bri + 1][nx][ny] = 1;
					enqueue(nx, ny, t.t + 1, t.bri + 1);
				}

				if (map[nx][ny] > 1 && visit[t.bri][nx][ny] == 0) // �־��� ���۱�
				{
					if (map[t.x][t.y] != 0 && map[t.x][t.y] > 1) // ���� �ٸ����� ���� ������ �ǳʹ�.
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
using namespace std;

int main(void)
{
	int i, j;
	int t;
	cin >> t;
	scanf("%d %d", &N, &M);

	for (int tc = 1; tc <= t; tc++) {

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			scanf("%d", &map[i][j]);

	int sol = bfs();

	printf("#%d %d\n", tc, sol);
}


	return 0;
}