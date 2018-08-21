#include<cstdio>
#include<cstring>
int map[502][502];
int isArrive[502][502];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int n,m;

int getNum(int r, int c) {
	if (r == n && c == m) {
		return 1;
	}
	int &ret = isArrive[r][c];
	if (ret != -1) return ret;
	ret = 0;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (map[nr][nc] == -1) continue;
		if (map[r][c] > map[nr][nc]) {
			ret += getNum(nr, nc);
		}
	}
	return ret;
}
int main() {
	scanf("%d %d\n", &n, &m);
	memset(map, -1, sizeof(map));
	memset(isArrive, -1, sizeof(isArrive));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) scanf("%d \n", &map[i][j]);
	}
	int res = getNum(1, 1);
	printf("%d\n", res);
	return 0;
}