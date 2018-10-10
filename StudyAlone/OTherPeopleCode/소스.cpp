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
			//���� ��ǥ�� x�ð���, store�� ����Ǿ��ִ� x�ð��� �ٸ� ���(que�� ����ִ� ������ x�ð��� �۾Ҵ� ���), pop���ֱ�
			if (store[x][y] != s) continue;
			//���� ������� �� �ִ� �ð��̶��, que�� �־��ֱ�
			if (isAlive(store[x][y], map[x][y])) {
				que.push_back({ x,y,s });
			}
			if (map[x][y] == -1) {
				for (int i = 0; i < 4; i++) {
					int nx = x + dx[i], ny = y + dy[i];
					//���� ������ x�ð��� �� ũ��, �� ���� �־��ֱ�
					if (!visited[nx][ny] && store[nx][ny] < s) {
						store[nx][ny] = s;
						map[nx][ny] = s;
						que.push_back({ nx,ny,s });
					}
				}
			}
		}
		//�� �ð����� Ȱ���� ��, ������ ���� ������ vistied�� �־��ֱ�(���� �ð����� visited�� ���� Ž���� �ʿ䰡 ����)
		for (int i = 0; i < que.size(); i++) if (!visited[que[i].x][que[i].y]) visited[que[i].x][que[i].y] = true;
	}

	//que�� ����ִ� ���� �� ���� ū ���� ������ ������ �ƴ� ���� ���ֱ�
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