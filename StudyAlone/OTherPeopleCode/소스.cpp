#include <iostream>
#include <deque>
#include <memory.h>
using namespace std;

struct cell { int x, y, s; };
int t, n, m, k, map[500][500], store[500][500], dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1 };
deque<cell> que;
bool visited[500][500];

bool isAlive(int x, int y) { return (x + y != 0); }
int spread() {
	int ret = 0;
	while (k--) {
		int size = que.size();
		while (size--) {
			int x = que.front().x, y = que.front().y, s = que.front().s;
			que.pop_front();
			--map[x][y];
			//지금 좌표의 x시간과, store에 저장되어있는 x시간이 다른 경우(que에 들어있는 세포의 x시간이 작았던 경우), pop해주기
			if (store[x][y] != s) continue;
			//아직 살아있을 수 있는 시간이라면, que에 넣어주기
			if (isAlive(store[x][y], map[x][y])) {
				que.push_back({ x,y,s });
			}
			if (map[x][y] == -1) {
				for (int i = 0; i < 4; i++) {
					int nx = x + dx[i], ny = y + dy[i];
					//현재 세포의 x시간이 더 크면, 이 값을 넣어주기
					if (!visited[nx][ny] && store[nx][ny] < s) {
						store[nx][ny] = s;
						map[nx][ny] = s;
						que.push_back({ nx,ny,s });
					}
				}
			}
		}
		//한 시간동안 활동한 후, 세포들 퍼진 정도를 vistied에 넣어주기(다음 시간에는 visited된 곳은 탐색할 필요가 없다)
		for (int i = 0; i < que.size(); i++) if (!visited[que[i].x][que[i].y]) visited[que[i].x][que[i].y] = true;
	}

	//que에 들어있는 값들 중 가장 큰 값을 가지는 세포가 아닌 경우는 빼주기
	while (!que.empty()) {
		int x = que.front().x, y = que.front().y, s = que.front().s;
		if (store[x][y] == s) {
			++ret; store[x][y] = 999;
		}
		que.pop_front();
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> k;
		for (int i = 0; i<n; i++)
			for (int j = 0; j < m; j++) {
				int x = 250 - n / 2 + i, y = 250 - m / 2 + j;
				cin >> map[x][y];
				if (map[x][y]) {
					store[x][y] = map[x][y];
					visited[x][y] = true;
					que.push_back({ x,y ,store[x][y] });
				}
			}
		cout << "#" << tc << " " << spread() << "\n";
		memset(map, 0, sizeof(map));
		memset(store, 0, sizeof(store));
		memset(visited, 0, sizeof(visited));
	}
}