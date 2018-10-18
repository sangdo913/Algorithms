#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;


int N, H, W; // 구슬, 행과 열
int board[16][13];
bool check[16][13];
int Answer;
int ans;
int xg[13]; // 0이 아닌 x 좌표 저장
int temp_board[16][13];
int temp_xg[13];
void down_block() {
	queue<int> qt;
	for (int i = 1; i <= W; i++) {
		for (int j = H; j >= 1; j--) {
			if (board[j][i] != 0)
				qt.push(board[j][i]);
		}
		int s = H - qt.size();
		if (s == H) // q에 아무것도 없으면 초기화
			xg[i] = 1;
		for (int j = H; j >= 1; j--) {
			if (j > s) {
				board[j][i] = qt.front(); qt.pop();
				xg[i] = j;
			}
			else
				board[j][i] = 0;
		}
	}
}
void calc(vector<int> vc) {
	queue<pair<int, int>> q;

	for (int i = 1; i <= W; i++) { //복사
		temp_xg[i] = xg[i];
	}
	for (int i = 1; i <= H; i++) { //복사
		for (int j = 1; j <= W; j++) {
			temp_board[i][j] = board[i][j];
		}
	}
	for (int t = 0; t<vc.size(); t++) {
		if (xg[vc[t]] == 1 && board[xg[vc[t]]][vc[t]] == 0) {
			continue;
		}
		q.push({ xg[vc[t]],vc[t] });
		for (int s = 1; s <= H; s++) {
			for (int k = 1; k <= W; k++) {
				check[s][k] = false;
			}
		}
		check[xg[vc[t]]][vc[t]] = true;
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			//cout << "x,y : " << x << ", " << y << '\n';
			q.pop();
			if (board[x][y] == 1) {
				board[x][y] = 0;
			}
			else {
				int k = board[x][y];
				board[x][y] = 0;
				for (int i = (-k + 1); i < k; i++) {
					int dx = x + i;
					if (dx >= 1 && dx <= H && check[dx][y] == false && board[dx][y] != 0) {
						check[dx][y] = true;
						q.push({ dx,y });
					}
				}
				for (int i = (-k + 1); i < k; i++) {
					int dy = y + i;
					if (dy >= 1 && dy <= W && check[x][dy] == false && board[x][dy] != 0) {
						check[x][dy] = true;
						q.push({ x,dy });
					}
				}
			}
		}
		down_block();

	}
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			if (board[i][j] != 0)
				Answer++;
		}
	}
	ans = min(Answer, ans); // 계산값과 현재 ans 중 작은 쪽을 ans에 대입
	for (int i = 1; i <= H; i++) { // 붙여넣기
		for (int j = 1; j <= W; j++) {
			board[i][j] = temp_board[i][j];
		}
	}
	for (int i = 1; i <= W; i++) { // 붙여넣기
		xg[i] = temp_xg[i];
	}
}
void dfs(int cnt, vector<int> vc) {
	if (cnt == N) {
		Answer = 0;
		calc(vc);
		return;
	}
	else {
		for (int i = 1; i <= W; i++) {
			vc.push_back(i);
			dfs(cnt + 1, vc);
			vc.pop_back();
		}
	}
}
int main() {
	int test_case;
	cin >> test_case;
	for (int tc = 1; tc <= test_case; tc++) {
		cin >> N >> W >> H;
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				board[i][j] = 0;
			}
		}
		for (int i = 1; i <= W; i++) {
			xg[i] = 1;
		}
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				cin >> board[i][j];
				if (board[i][j] == 0) {
					xg[j] = i + 1;
				}
			}
		}
		ans = INT_MAX;
		vector<int> k; //빈 벡터 생성
		dfs(0, k);
		cout << "#" << tc << " " << ans << '\n';
	}
}