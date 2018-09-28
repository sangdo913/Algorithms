#include <iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

bool map[10][10];
bool visit[10][10];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int N;
vector<int> vec;


int bfs(int r, int c) {
	queue<pair<int, int> > que;

	visit[r][c] = true;

	que.push({ r,c });

	int res = 0;

	while (que.size()) {
		auto now = que.front();
		que.pop();
		res++;

		for (int d = 0; d < 4; d++) {
			pair<int, int> next;
			next.first = now.first + dr[d];
			next.second = now.second + dc[d];

			if (next.first < 0 || next.first > N - 1 || next.first < 0 || next.second > N - 1) continue;
			if (visit[next.first][next.second]) continue;
			visit[next.first][next.second] = true;
			if (map[next.first][next.second]) {
				que.push(next);
			}
		}
	}

	return res;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == false && map[i][j]) {
				vec.push_back(bfs(i, j));
			}
		}
	}

	sort(vec.begin(), vec.end());

	cout << vec.size() << '\n';


	for (auto it : vec) {
		cout << it << ' ';
	}
	if(vec.size()) cout << '\n';
	return 0;
}