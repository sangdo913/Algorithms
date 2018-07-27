//  4740_밍이의 블록게임
//  Created by yeram Kim on 2018. 7. 27..

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int N, M;
char map[35][35];

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

void print_map() {
	int i, j;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}

	printf("\n");
}

bool in_range(int x, int y) {
	if (x >= 1 && x <= N && y >= 1 && y <= M)
		return true;
	else return false;
}

void falling() {
	int i, j;
	for (i = 1; i <= M; i++) {
		queue<char> q;
		for (j = N; j >= 1; j--) {
			if (map[j][i] != '#')
				q.push(map[j][i]);
		}

		int k = N;
		while (!q.empty()) {
			char c = q.front();
			q.pop();
			map[k][i] = c;
			k--;
		}

		k++;

		k--;
		while (k >= 1) {
			map[k][i] = '#';
			k--;
		}


	}
}

void up(char s[31]) {
	int i, j;

	for (i = 1; i <= M; i++) {
		if (map[1][i] != '#') {
			return;
		}
	}

	for (i = 1; i<N; i++) {
		for (j = 1; j <= M; j++) {
			map[i][j] = map[i + 1][j];
		}
	}

	for (j = 1; j <= M; j++)
		map[N][j] = s[j - 1];

	falling();

}

void down() {
	int max = 0;
	vector<pair<int, int>> v;
	int i, j, k;
	bool visit[35][35] = { { false } };

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= M; j++) {
			if (map[i][j] != '#') {
				char c = map[i][j];
				int n = 1;
				queue<pair<int, int>> q;
				q.push({ i,j });

				while (!q.empty()) {
					int x = q.front().first;
					int y = q.front().second;
					q.pop();
					for (k = 0; k<4; k++) {
						int n_x = x + dx[k];
						int n_y = y + dy[k];
						if (in_range(n_x, n_y) && map[n_x][n_y] == c && !visit[n_x][n_y]) {
							q.push({ n_x,n_y });
							visit[n_x][n_y] = true;
							n++;
						}
					}
				}

				if (n>max) {
					max = n;
					v.clear();
					v.push_back({ i,j });
				}
				else if (n == max) {
					v.push_back({ i,j });
				}
			}
		}
	}

	for (i = 0; i<v.size(); i++) {
		int x = v.at(i).first;
		int y = v.at(i).second;
		char c = map[x][y];
		map[x][y] = '#';
		queue<pair<int, int>> q;
		q.push({ x,y });

		while (!q.empty()) {
			x = q.front().first;
			y = q.front().second;
			q.pop();
			for (k = 0; k<4; k++) {
				int n_x = x + dx[k];
				int n_y = y + dy[k];

				if (in_range(n_x, n_y) && map[n_x][n_y] == c) {
					map[n_x][n_y] = '#';
					q.push({ n_x,n_y });
				}

			}
		}
	}

	falling();

}

void left() {
	int i, j;
	for (i = 1; i <= N; i++) {
		queue<char> q;
		for (j = 1; j <= M; j++) {
			if (map[i][j] != '#')
				q.push(map[i][j]);
		}

		int k = 1;
		while (!q.empty()) {
			map[i][k] = q.front();
			q.pop();
			k++;
		}

		while (k <= M) {
			map[i][k] = '#';
			k++;
		}
	}
}

void right() {
	int i, j;
	for (i = 1; i <= N; i++) {
		queue<char> q;
		for (j = M; j >= 1; j--) {
			if (map[i][j] != '#')
				q.push(map[i][j]);
		}

		int k = M;
		while (!q.empty()) {
			map[i][k] = q.front();
			q.pop();
			k--;
		}

		while (k >= 1) {
			map[i][k] = '#';
			k--;
		}
	}
}

int main(int argc, const char * argv[]) {

	int T;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++) {
		int Q;
		scanf("%d %d %d", &N, &M, &Q);

		int i, j;
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= M; j++) {
				if (j == 1)
					scanf(" %c", &map[i][j]);
				else scanf("%c", &map[i][j]);

			}
		}

		//    print_map();

		for (i = 1; i <= Q; i++) {
			char q;
			scanf(" %c", &q);
			if (q == 'U') {
				char s[31];
				scanf("%s", s);
				up(s);
				//        print_map();
			}
			else if (q == 'D') {
				down();
				//         print_map();
			}
			else if (q == 'L') {
				left();
				//         print_map();
			}
			else if (q == 'R') {
				right();
				//        print_map();
			}

		}

		printf("#%d\n", test_case);
		print_map();

	}

	return 0;
}
