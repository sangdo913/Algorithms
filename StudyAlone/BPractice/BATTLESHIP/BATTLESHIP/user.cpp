#define MISS		0
#define CARRIER		1
#define BATTLESHIP	2
#define CRUISER		3
#define SUBMARINE	4
#define DESTROYER	5

extern int fire(int r, int c);

struct COD {
	int x, y;
};

int board[10][10];
int tc = 0;
int llen[6];
int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };
int size[6] = { 0,5,4,3,3,2 };
int complete[6];

bool isout(int i, int j) { return i < 0 || i >= 10 || j < 0 || j >= 10; }
int priority[10][10];

void check(int rr, int cc, int d, int type) {
	int check = 0;

	int r = rr, c = cc;
	for (int i = 0; i < size[type]; ++i, r += dr[d], c += dc[d]) {
		if (isout(r, c) || (board[r][c] >= tc && board[r][c] != tc + type)) return;
		check += board[r][c] == tc + type;
	}

	int plus = size[type];
	if (llen[type]) plus += size[type]*1000;
	if (llen[type] && check != llen[type]) return;

	r = rr, c = cc;
	for (int i = 0; i < size[type]; ++i, r += dr[d], c += dc[d]) {
		priority[r][c] += plus;
	}
}

int cnt = 0;

void init(int limit)
{
}

void play()
{
	cnt = 17;
	for (int i = 1; i < 6; ++i) llen[i] = 0;
	tc += 6;

	while (cnt) {
		int num = 0;
		int temp = 0;
		COD ret;

		for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) priority[i][j] = 0;

		for (int i = 0; i < 10; ++i)for (int j = 0; j < 10; ++j) {
			for (int type = 1; type < 6; ++type) {
				if (complete[type] == tc) continue;

				for (int d = 0; d < 4; ++d) {
					check(i, j, d, type);
				}
			}
		}
		for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) {
			if (board[i][j] >= tc) continue;
			if (num < priority[i][j]) {
				ret.x = i, ret.y = j;
				num = priority[i][j];
			}
		}

		int type = fire(ret.x, ret.y);

		if (type) {
			cnt--;
			llen[type]++;
			if (llen[type] == size[type]) complete[type] = tc;
		}

		board[ret.x][ret.y] = tc + type;
	}
}