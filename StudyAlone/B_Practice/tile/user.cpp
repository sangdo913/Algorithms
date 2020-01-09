static const int MAX_N =  105;
const int HSIZE = 108;
#define rint register int

extern int get_N(void);
extern char get_A(int row, int col);

long long MASK[HSIZE][HSIZE];
int getbit[1 << 16];
long long A[HSIZE][HSIZE];
long long B[HSIZE][HSIZE];

bool ismade;
void init(int testcase) {
	rint N = get_N();
	rint l = N;
	for (rint i = 0; i < (1 << 16); ++i) {
		rint num = 0;
		rint b = i;
		while (b) num++, b -= b & -b;
		getbit[i] = num;
	}

	for (rint i = 0; i < N; ++i) {
		for (rint j = 0; j < N; ++j) {
			A[i][j] = 0;
			for (rint r = 0; r < 8; ++r) {
				for (rint c = 0; c < 8; ++c) {
					long long a = get_A(i + r, j + c);
					a = a == -1 ? 0 : a - '0';
					A[i][j] |= a << (8*r+c);
				}
			}
		}
	}
}
int getSimilar(int M, char BB[MAX_N][MAX_N]) {
	char myb[HSIZE][HSIZE] = {};
	for (rint i = 0; i < M; ++i) {
		for (rint j = 0; j < M; ++j) {
			myb[i][j] = BB[i][j] - '0';
		}
	}
	for (rint i = 0; i < M; i+=8) {
		for (rint j = 0; j < M; j+=8) {
			rint rr = i / 8, cc = j / 8;
			MASK[rr][cc] = B[rr][cc] = 0;

			for (rint r = 0; r < 8; ++r) {
				for (rint c = 0; c < 8; ++c) {
					B[rr][cc] |= (long long)myb[i + r][j + c] << (8 * r + c);
					if(i + r < M && j + c < M) MASK[rr][cc] |= (1LL << (8 * r + c));
				}
			}
		}
	}
	rint ret = 0;

	rint N = get_N();
	rint m = (M + 7) / 8;
	for (rint i = 0; i <= N-M ; ++i) {
		for (rint j = 0; j <= N - M; ++j) {
			rint num = 0;
			for (rint r = 0; r < m; ++r) {
				for (rint c = 0; c < m; ++c) {
				    register long long bit = ~(A[i + 8 * r][j + 8 * c] ^ B[r][c]) & MASK[r][c];
					for (rint cnt = 0; cnt < 4; ++cnt) {
						rint mybit = bit & 0xffff;
						num += getbit[mybit];
						bit >>= 16;
					}
				}
			}
			if (ret < num) {
				ret = num;
			}
		}
	}

	return ret;
}