typedef struct
{
	int y, x;
}AXIS;

#define RANGE 100
#define SCREENSIZE 1000
struct MEMO {
	int y, x, h, w;
	char memo[50][50];
	int msize;
	MEMO *n[SCREENSIZE / RANGE + 1][SCREENSIZE/RANGE+1];
	MEMO *p[SCREENSIZE / RANGE + 1][SCREENSIZE / RANGE + 1];
}memoes[10000];
#define rint register int

MEMO myhead[SCREENSIZE / RANGE + 1][SCREENSIZE / RANGE + 1];
int query;
int tc;
void init(int mScreenSize)
{
	++tc;
	for(rint i = 0; i < SCREENSIZE / RANGE+1; ++i) for(rint j = 0; j < SCREENSIZE / RANGE + 1; ++j) myhead[i][j].n[i][j] = myhead[i][j].p[i][j] = &myhead[i][j];
}
void create_memo(int mId, int mY, int mX, int mHeight, int mWidth, char str[])
{
	register MEMO& m = memoes[mId];
	memoes[mId].y = mY;
	memoes[mId].x = mX;
	memoes[mId].h = mHeight;
	memoes[mId].w = mWidth;
	memoes[mId].msize = 0;

	while (memoes[mId].msize < mHeight * mWidth && str[memoes[mId].msize]) 
		memoes[mId].memo[memoes[mId].msize/mWidth][memoes[mId].msize%mWidth]= str[memoes[mId].msize], 
		memoes[mId].msize++;

	for (rint i = mY / RANGE; i <= (mY + mHeight - 1) / RANGE; ++i) {
		for (rint j = mX / RANGE; j <= (mX + mWidth - 1) / RANGE; ++j) {
			m.n[i][j] = myhead[i][j].n[i][j];
			m.p[i][j] = &myhead[i][j];

			myhead[i][j].n[i][j]->p[i][j] = &m;
			myhead[i][j].n[i][j] = &m;
		}
	}
}

AXIS select_memo(int mId)
{
	register MEMO & m = memoes[mId];
	rint x = m.x, y = m.y, h = m.h, w = m.w;

	for (rint i = y / RANGE; i <= (y + h - 1) / RANGE; ++i) {
		for (rint j = x / RANGE; j <= (x + w - 1) / RANGE; ++j) {
			m.p[i][j]->n[i][j] = m.n[i][j];
			m.n[i][j]->p[i][j] = m.p[i][j];

			m.n[i][j] = myhead[i][j].n[i][j];
			m.p[i][j] = &myhead[i][j];

			myhead[i][j].n[i][j]->p[i][j] = &m;
			myhead[i][j].n[i][j] = &m;
		}
	}

	return { memoes[mId].y, memoes[mId].x };
}

void move_memo(int mId, int mY, int mX)
{
	register MEMO &m = memoes[mId];
	rint x = m.x, y = m.y, h = m.h, w = m.w;

	for (rint i = y / RANGE; i <= (y + h - 1) / RANGE; ++i) {
		for (rint j = x / RANGE; j <= (x + w - 1) / RANGE; ++j) {
			m.p[i][j]->n[i][j] = m.n[i][j];
			m.n[i][j]->p[i][j] = m.p[i][j];
		}
	}

	memoes[mId].y = mY;
	memoes[mId].x = mX;
	x = m.x, y = m.y;
	for (rint i = y / RANGE; i <= (y + h - 1) / RANGE; ++i) {
		for (rint j = x / RANGE; j <= (x + w - 1) / RANGE; ++j) {
			m.n[i][j] = myhead[i][j].n[i][j];
			m.p[i][j] = &myhead[i][j];

			myhead[i][j].n[i][j]->p[i][j] = &m;
			myhead[i][j].n[i][j] = &m;
		}
	}
}

void modify_memo(int mId, int mHeight, int mWidth, char str[])
{
	register MEMO&m = memoes[mId];
	rint x = m.x, y = m.y, h = m.h, w = m.w;

	for (rint i = y / RANGE; i <= (y + h - 1) / RANGE; ++i) {
		for (rint j = x / RANGE; j <= (x + w - 1) / RANGE; ++j) {
			m.p[i][j]->n[i][j] = m.n[i][j];
			m.n[i][j]->p[i][j] = m.p[i][j];
		}
	}

	h = memoes[mId].h = mHeight;
	w = memoes[mId].w = mWidth;
	
	rint& msize = memoes[mId].msize;
	msize = 0;

	while (msize < mHeight * mWidth && str[msize]) {
		memoes[mId].memo[msize / mWidth][msize%mWidth] = str[msize];
		msize++;
	}

	for (rint i = y / RANGE; i <= (y + h - 1) / RANGE; ++i) {
		for (rint j = x / RANGE; j <= (x + w - 1) / RANGE; ++j) {
			m.n[i][j] = myhead[i][j].n[i][j];
			m.p[i][j] = &myhead[i][j];

			myhead[i][j].n[i][j]->p[i][j] = &m;
			myhead[i][j].n[i][j] = &m;
		}
	}
}
char res[5][5];
int myvisit[5][5];
void get_screen_context(int mY, int mX, char res[5][5])
{
	for (rint i = 0; i < 5; ++i) for (rint j = 0; j < 5; ++j) res[i][j] = 0, myvisit[i][j] = 0x3f3f3f3f;
	query++;
	rint yy = mY / RANGE;
	rint xx = mX / RANGE;
	int complete = 0;

	for (rint i = yy - 1; i <= yy + 1; ++i) {
		if (i < 0 || i == 11) continue;
		if (complete == 25) break;
		for (rint j = xx - 1; j <= xx + 1; ++j) {
			if (j < 0 || j == 11) continue;
			if (complete == 25) break;
			register MEMO *ed = &myhead[i][j];
			register MEMO *cur = ed->n[i][j];
			while (cur != ed && complete != 25) {
				rint sy = cur->y;
				rint ey = sy + cur->h - 1;
				rint sx = cur->x;
				rint ex = sx + cur->w - 1;
				sy = sy < i*RANGE ? i * RANGE : sy;
				ey = (i + 1)*RANGE - 1 < ey ? (i + 1)*RANGE - 1 : ey;
				sx = sx < j * RANGE ? j * RANGE : sx;
				ex = (j + 1)*RANGE - 1 < ex ? (j + 1)*RANGE - 1 : ex;
				if (sx <= mX && mX <= ex || sx <= mX + 4 && mX + 4 <= ex || mX <= sx && sx <= mX+4 || mX <= ex && ex <= mX+4) 
					if(sy <= mY && mY <= ey || sy <= mY +4 && mY+4 <= ey || mY <= sy && sy <= mY+4 || mY <= ey && ey <= mY +4) {
					sx = sx < mX ? mX : sx;
					ex = mX + 4 < ex ? mX + 4 : ex;
					sy = sy < mY ? mY : sy;
					ey = mY + 4 < ey ? mY + 4 : ey;

					for (rint y = sy; y <= ey; ++y) {
						for (rint x = sx; x <= ex; ++x) {
							if (myvisit[y-mY][x-mX] == query) continue;
							myvisit[y-mY][x-mX] = query;
							complete++;
							res[y - mY][x - mX] = (y - cur->y)*cur->w + x - cur->x < cur->msize? cur->memo[y - cur->y][x - cur->x] : 0;
						}
					}
				}
				cur = cur->n[i][j];
			}

		}
	}
}