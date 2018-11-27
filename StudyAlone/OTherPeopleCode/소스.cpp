#include <iostream>
using namespace std;

#define qq 100000

class Pair {
public:
	int x, y;
	bool check;
};

template <typename T>
class Queue {
public:
	int front, rear, size;
	T arr[qq + 1];
	Queue() {
		front = rear = size = 0;
	}
	void push(T item) {
		rear++;
		rear = rear % qq;
		arr[rear] = item;
		++size;
	}
	T pop() {
		front++;
		front = front % qq;
		--size;
		return arr[front];
	}
	T peek() { return arr[front]; }
	bool empty() { return size == 0; }
	void clear() { front = rear = size = 0; }
};

int n, m, time1;
Queue<Pair> q;
int map[11][11];
bool visit[11][11];
int dx[] = { 1,0,-1,0 }, dy[] = { 0,1,0,-1 };

void bfs() {
	q.push({ 0,0,0 });
	visit[0][0] = 1;
	while (!q.empty()) {
		int qSize = q.size;
		++time1;

		while (qSize--) {
			Pair p = q.pop();
			if (map[p.x][p.y] == 1) q.push({ p.x, p.y, 0 }); // 절벽만 아니면 가만히 멈춰있는것도 가능

			for (int i = 0; i < 4; i++) {
				int nx = p.x + dx[i];
				int ny = p.y + dy[i];
				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
				if (visit[nx][ny]) continue;
				if (nx == n - 1 && ny == n - 1) {
					if (!p.check) {
						return;
					}
					else {
						if (map[nx][ny] != 1) continue;
						else return;
					}
				}
				if (map[nx][ny] == 1) { // 갈수 있는 길
					visit[nx][ny] = 1;
					q.push({ nx, ny, p.check });
				}
				else if (map[nx][ny] == 0) { // m일때 지나갈수 있음
					if (!p.check && time1%m == 0) { // 이전에 오작교를 안건넜고, 다음 오작교가 열리면
						visit[nx][ny] = 1;
						q.push({ nx,ny, 1 });
					}
				}
				else { // 해당 시간의 배수일때만 지나갈수 있음
					if (!p.check && time1%map[nx][ny] == 0) { // 이전에 오작교를 안건넜고, 다음 오작교가 열리면
						visit[nx][ny] = 1;
						q.push({ nx,ny, 1 });
					}
				}
			}
		}
	}
}

void init() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visit[i][j] = 0;
		}
	}
	q.clear();
	time1 = 0;
}

int main() {
	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
			}
		}

		init();
		bfs();

		cout << "#" << t << " " << time1 << endl;
	}
}