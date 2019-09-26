#include<cstdio>

int T, N;
int arr[2][21][21];
int num[21][21];
int board[2][21][21];
int candigit[21][21];
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
		br += dr[d];
		bc += dc[d];
		int cnt = 0;
		int s = 0, n = 0;
		int r = 0;

		while (!isout(br, bc) && arr[0][br][bc]) {
			if (num[br][bc]) {
				r |= (1 << (num[br][bc] - 1));
			}
			cnt++, br += dr[d], bc += dc[d];
		}
		ret &= remain[allsum][cnt][r];
	}
	return ret;
}

int getnext() {
	int cod = -1;
	int r = -1, c;
	int mmax = 0x3f3f3f3f;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (!arr[0][i][j]) continue;
			if (num[i][j]) continue;
			int digitnum = getbit(candigit[i][j] & getPossible(i, j));

			if (digitnum < mmax) {
				mmax = digitnum;
				cod = (i << 10) + j;
				r = i, c = j;
			}
		}
	}
	return cod != -1 ? (r<<10) + c : -1;
}
//#define getbase(br,bc, i) ((br = arr[i][br][bc] >> 10), (bc = arr[i][br][bc] & ((1<<10)-1)))
#define getget(br,bc,nr,nc,i) ((br) = ((arr[i][nr][nc]) >> 10)), ((bc) = ((arr[i][nr][nc]) &((1<<10)-1)))

struct COD {
	int x, y;
};

COD nextcod(int r, int c, int d) {
	COD res = { -2 };
	int nr, nc;
	getget(nr, nc,r,c, d);
	r += dr[d], c += dc[d];
	int mmin = 0x3f3f3f3f;
	while (!isout(r, c) && arr[0][r][c]) {
		if (!num[r][c]) {
			int b = getPossible(r, c);
			if (!b) return { -1 };
			b = getbit(b);
			if (mmin > b) {
				res.x = r, res.y = c;
				mmin = b;
			}
		}
		r += dr[d], c += dc[d];
	}
	
	return res;
}


bool make(int r, int c, int d) {
	if (r == -2) {
		int cod = getnext();
		if (cod == -1) return true;

		int nr = cod >> 10, nc = cod & ((1 << 10) - 1);
		return make(nr,nc, d ^ 1);
	}

	int allpossible = candigit[r][c] & getPossible(r, c);
	int nr, nc;
	getget(nr, nc, r, c, d);
	
	nr += dr[d], nc += dc[d];
	int st[10], sz = 0;
	while(!isout(nr,nc) && arr[0][nr][nc]){
		st[sz++] = num[nr][nc];
		nr += dr[d], nc += dc[d];
	}

	for (int i = 0; i < 9; ++i) {
		if (allpossible & (1 << i)) {
			num[r][c] = i + 1;
			COD n = nextcod(r, c, d);
			if (n.x == -1) {
				getget(nr, nc, r, c, d);
				nr += dr[d], nc += dc[d];

				for (int i = 0; i < sz; ++i, nr += dr[d], nc += dc[d]) {
					num[nr][nc] = st[i];
				}
				return false;
			}
			bool res =  make(n.x, n.y, d);
			if (res) return true;
			nr = r, nc = c;
			getget(nr, nc, r, c, d);
			nr += dr[d], nc += dc[d];
			for (int i = 0; i < sz; ++i, nr += dr[d], nc += dc[d]) {
				num[nr][nc] = st[i];
			}
		}
	}

	getget(nr, nc, r, c, d);
	nr += dr[d], nc += dc[d];
	for (int i = 0; i < sz; ++i, nr += dr[d], nc += dc[d]) {
		num[nr][nc] = st[i];
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
				scanf("%d", arr[0][i] + j);
				if (arr[0][i][j]) candigit[i][j] = (1 << 9) - 1;
			}
		}

		int m;

		scanf("%d", &m);
		int r, c, vertical;
		while (m--) {
			scanf("%d %d %d", &r, &c, &vertical);
			scanf("%d", &board[vertical][r][c]);
			int cnt = 0;
			int nr = r + dr[vertical], nc = c + dc[vertical];
			while (!isout(nr, nc) && arr[0][nr][nc]) {
				arr[vertical][nr][nc] = (r << 10) + c;
				cnt++;
				nr += dr[vertical];
				nc += dc[vertical];
			}
			count[vertical][r][c] = cnt;
			nr = r + dr[vertical], nc = c + dc[vertical];
			while (cnt--) {
				candigit[nr][nc] &= possibledp[count[vertical][r][c]][board[vertical][r][c]];
				nr += dr[vertical], nc += dc[vertical];
			}
		}

		int cod;
		cod = getnext();
			int br = cod >> 10;
			int bc = cod & ((1 << 10) - 1);

			bool res = make(br + dr[0], bc + dc[0], 0);

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				printf("%d ", num[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}