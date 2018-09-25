#include<iostream>
#include<queue>
#include<algorithm>
#define dbg cout << "Debugging\n"; 
#define N 101
using namespace std;
char a[N][N]; int n, m;  bool vist[N][N]; int x, y;
int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };
int Up, Down, Left, Right;   int U_l, U_r, D_l, D_r, L_l, L_r, R_l, R_r;
vector<char> ans;    int dp, cc = -1;
void clear() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			vist[i][j] = 0;
}
bool Simul() {   // dp -> cc 탐색 
	if (dp == 0) {         // 위
		if (cc == -1) {   // 위에서 왼쪽을 바라볼 경우 
			int nx = Up + dx[dp]; int ny = U_l + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
		else if (cc == 1) {  // 위에서 오른쪽을 바라볼 경우
			int nx = Up + dx[dp]; int ny = U_r + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
	}
	else if (dp == 1) {    // 오른쪽
		if (cc == -1) {  // 오른쪽에서 왼쪽을 바라볼 경우
			int nx = R_l + dx[dp]; int ny = Right + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
		else if (cc == 1) {  // 오른쪽에서 오른쪽을 바라볼경우
			int nx = R_r + dx[dp]; int ny = Right + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
	}
	else if (dp == 2) {    // 아래쪽
		if (cc == -1) {   // 아래쪽에서 왼쪽을 바라볼경우
			int nx = Down + dx[dp]; int ny = D_l + dy[dp];   // dp방향만큼 전진했을때 다음블록이 접해진다면
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false; // 아닐경우 바로 false리턴 
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
		else if (cc == 1) {
			int nx = Down + dx[dp]; int ny = D_r + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
	}
	else if (dp == 3) {     // 왼쪽 
		if (cc == -1) {
			int nx = L_l + dx[dp]; int ny = Left + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
		else if (cc == 1) {
			int nx = L_r + dx[dp]; int ny = Left + dy[dp];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
			if (a[nx][ny] == 'X') return false;
			x = nx; y = ny;
		}
	}
	return true;
}
void Calc(int x, int y) {

	if (Up > x)
		Up = x, U_l = y, U_r = y;
	else if (Up == x)
		U_l = min(U_l, y), U_r = max(U_r, y);
	if (Down < x)
		Down = x, D_l = y, D_r = y;
	else if (Down == x)
		D_l = max(D_l, y), D_r = min(D_r, y);
	if (Right < y)
		Right = y, R_r = x, R_l = x;
	else if (Right == y)
		R_r = max(R_r, x), R_l = min(R_l, x);
	if (Left > y)
		Left = y, L_l = x, L_r = x;
	else if (Left == y)
		L_l = max(L_l, x), L_r = min(L_r, x);
}
bool bfs(int x, int y, char pivot) {
	queue<pair<int, int>> q;
	if (!vist[x][y])
		q.push({ x, y });
	Up = x, Down = x, Left = y, Right = y;
	U_l = y, U_r = y; D_l = y, D_r = y;
	L_l = x, L_r = x; R_l = x, R_l = x;
	bool res = false;
	while (!q.empty()) {
		res = true;
		int x1 = q.front().first; int y1 = q.front().second;
		q.pop();
		Calc(x1, y1);
		vist[x1][y1] = true;
		for (int i = 0; i < 4; i++) {
			int xx = x1 + dx[i]; int yy = y1 + dy[i];
			if (xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
			if (a[xx][yy] == pivot && !vist[xx][yy]) {
				vist[xx][yy] = true;
				q.push({ xx, yy });
			}
		}
	}
	return res;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> n >> m;
	dp = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
	bool res = true;
	while (res) {
		/*if (a[x][y] == 'Z') {
		cout << Up << ' ' << Down << '\n';
		cout << U_l << ' ' << U_r << ' ' << D_l << ' ' << D_r << '\n';
		}*/
		res = false;
		clear();
		if (bfs(x, y, a[x][y])) {
			ans.push_back(a[x][y]);
			for (int i = 0; i < 4; i++) {  // dp설정
				for (int j = 0; j < 2; j++) {   // cc설정
					if (Simul()) {  // 다음블록이 탐색되는지를 결정
						res = true;
						break;
					}
					else {
						if (!j)	cc *= -1;
						else break;
					}
				}
				if (res)  // 다음블록 설정이 완료됨
					break;
				else {   // 다음블록 설정이 완료되지 않음 
					dp += 1; dp %= 4;  // 시계방향 이동
				}
			}
		}
		if (!res) break;
	}
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i];
	return 0;
}