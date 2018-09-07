#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int map[11][11];
int check[11][11];
int N, M, ans, T;
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };
int noX;
int noY;
bool use;
void getCross()
{
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] == 1) continue;
			//해당 좌표에서 4면을 확인 
			cnt = 0;
			for (int k = 0; k < 4; k++)
			{
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny<0 && ny>N - 1 && nx<0 && nx>N - 1) continue;
				if (map[ny][nx] != 1) cnt++;
			}
			if (cnt >= 3)
			{
				noX = j;
				noY = i;
				return;
			}
		}
	}
}
bool isSafe(int y, int x)
{
	return (y >= 0 && y <= N - 1 && x >= 0 && x <= N - 1);
}
//y,x좌표,시간
void dfs(int y, int x, int time)
{
	if (!isSafe(y, x)) return;
	if (y == noY && x == noX) return;
	if (check[y][x] <= time) return;
	check[y][x] = time;
	//printf("y=%d x=%d time=%d\n",y,x,time);
	if (y == N - 1 && x == N - 1)
	{
		ans = min(ans, time);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!isSafe(ny, nx)) continue;
		//if (check[ny][nx]) continue;
		if (map[ny][nx] == 0) continue;
		if (map[ny][nx] == 1)
		{
			dfs(ny, nx, time + 1);
		}
		else if (map[ny][nx] > 1)
		{
			int wait = map[ny][nx];
			dfs(ny, nx, time + wait - (time%wait));
		}
		//check[ny][nx] = false;
	}
	return;
}
void init()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) check[i][j] = false;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M;
		int tmp = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> tmp;
				map[i][j] = tmp;
				check[i][j] = false;
			}
		}

		getCross();
		ans = 1e9;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] != 0) continue;
				if (map[i][j] == 0)
					map[i][j] = M;

				init();
				memset(check, 0x3f, sizeof(check));
				dfs(0, 0, 0);
				map[i][j] = 0;
			}

		}
		cout << "#" << tc << " " << ans << "\n";
	}
}