#include<cstdio>

int T, N;
int arr[2][21][21];
int	filled[2][21][21];
int num[21][21];
int board[2][21][21];
int possibledp[10][46];
int remain[50][10][1 << 9];
int count[2][21][21];

int dr[2] = { 0, 1 };
int dc[2] = { 1,0 };

bool isout(int r, int c) {
	return r <= 0 || r > N || c <= 0 || c > N;
}

int getbit(int bit) {
	int ret = 0;
	while (bit) {
		ret++;
		bit -= bit & -bit;
	}
	return ret;
}


int getPossible(int r, int c) {
	int ret = (1 << 10) - 1;
	for (int d = 0; d < 2; ++d) {
		int br = arr[d][r][c] >> 10;
		int bc = arr[d][r][c] & ((1 << 10) - 1);
		int allsum = board[d][br][bc];
		
		ret &= remain[allsum][count[d][br][bc]][filled[d][br][bc]];
	}
	return ret;
}

int getnext() {
	int cod = -1;
	int r = -1, c;
	int mmax = 0x3f3f3f3f;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (!arr[0][i][j]) {
				continue;
			}
			if (num[i][j]) continue;
			int digitnum =  getPossible(i, j);
			if (!digitnum) return -2;
			if (digitnum < mmax) {
				mmax = digitnum;
				cod = (i << 10) + j;
				r = i, c = j;
			}
		}
	}
	return cod != -1 ? (r << 10) + c : -1;
}

bool dfs() {
	int cod = getnext();
	if (cod == -2) return false;
	if (cod == -1)return true;
	int r = cod >> 10;
	int c = (cod &((1 << 10) - 1));
	int avail = getPossible(r, c);
	int r1 = arr[0][r][c] >> 10, c1 = arr[0][r][c] & ((1 << 10) - 1);
	int r2 = arr[1][r][c] >> 10, c2 = arr[1][r][c] & ((1 << 10) - 1);

	for (int i = 0; i < 9; ++i) {
		if ((1 << i) & avail) {
			num[r][c] = i + 1;
			filled[0][r1][c1] += 1 << i;
			filled[1][r2][c2] += 1 << i;
			bool ed = dfs();
			if (ed) return true;
			filled[0][r1][c1] -= 1 << i;
			filled[1][r2][c2] -= 1 << i;
			num[r][c] = 0;
		}
	}
	return false;
}

int main() {
	scanf("%d", &T);

	for (int i = 0; i < (1 << 9); ++i) {
		int sum = 0, num = 0;
		int bit = i;
		int j = 1;
		while (bit) {
			if (bit & 1) {
				sum += j;
				num++;
			}
			++j, bit >>= 1;
		}

		for (int j = 0; j < i; ++j) {
			if ((j & i) == j) {
				remain[sum][num][j] |= i - j;
			}
		}
		possibledp[num][sum] |= i;
	}

	while (T--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				num[i][j] = 0;
				filled[0][i][j] = filled[1][i][j] = 0;
				scanf("%d", arr[0][i] + j);
			}
		}

		int m;

		scanf("%d", &m);
		int r, c, vertical;
		while (m--) {
			scanf("%d %d %d", &r, &c, &vertical);
			scanf("%d", &board[vertical][r][c]);
			int nr = r + dr[vertical], nc = c + dc[vertical];
			int cnt = 0;
			while (!isout(nr, nc) && arr[0][nr][nc]) {
				arr[vertical][nr][nc] = (r << 10) + c;
				cnt++;
				nr += dr[vertical];
				nc += dc[vertical];
			}
			count[vertical][r][c] = cnt;
		}
		dfs();
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j) {
				printf("%d ",num[i][j]);
			}
			printf("\n");
		}

	}
	return 0;
}