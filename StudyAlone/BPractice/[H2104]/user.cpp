#include<cstdio>
#define rint register int
#define TSIZE 3001
#define MIN(a,b) ((a) < (b)) ? (a) : (b)
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
int tc;
int R, C;

int conv[256];
int nnode[TSIZE][26];
int tnode[TSIZE][26];
int nid, tid;
int tv[3001][300];
int tvsize[3001];
int tS[3001];

int imap[3001];
int chk[3001];
int iid;

int itemT[3001];
int itemR[3001];
int itemC[3001];
int itemH[3001];
int itemW[3001];
int floor[601][601];
int itemValid[3001];
char mname[3001][11];
int nlen[3001];
char mtag[3001][11];
int tlen[3001];

void init(int r, int c) {
	for (rint i = 0; i < nid; ++i) for (rint j = 0; j < 26; ++j) nnode[i][j] = 0;
	for (rint i = 0; i < tid; ++i) for (rint j = 0; j < 26; ++j) tnode[i][j] = 0;
	tc++;
	R = r, C = c;
	for (rint i = 0; i < tid; ++i) {
		tvsize[i] = 0;
		tS[i] = 0;
	}
    iid= 0;

	for (rint i = 'a'; i <= 'z'; ++i) {
		conv[i] = i - 'a';
	}

	rint b = R * C;
	int cnt = 0;
	// while (b) {
	// 	for (rint i = 1; i <= R; ++i) {
	// 		for (rint j = 1; j <= C; ++j) {
	// 			v[cnt][i][j] = 0;
	// 		}
	// 		b /= 4;
	// 		cnt++;
	// 	}
	// }
	nid = tid = 1;
}

// int findauto(int d, int a, int b, int r, int c, int h, int w, int mh, int mw, int minh, int minw){
// 	a = a * 2 - 1;
// 	b = b*2 - 1;
// 	if (!h || !w) return (1000 << 10) + 1000;
// 	if (h == 1 && w == 1) {
// 		if (mh == 1 && mw == 1) return (r << 10) + c;
// 		return (1000<<10) + 1000;
// 	}
// 	if (r >= minh || c >= minw) {
// 		return (1000 << 10) + 1000;
// 	}
// 	int ret = (1000 << 10 ) + 1000;
// 	if (mh*mw <= h*w - v[d][a][b]) {
// 		int res = findauto(d + 1, a, b, r, c, h / 2, w / 2,mh,mw, minh, minw);
// 		ret = MIN(res, ret);
// 		res = findauto(d + 1, a + 1, b, r + h / 2, c, h-h/2, w/2, mh, mw, ret &0x3ff , ret>>10);
// 		ret = MIN(res, ret);
// 		res = findauto(d + 1, a, b + 1, r, c + w / 2,h/2, w-w/2, mh, mw, ret & 0x3ff, ret>>10);
// 		ret = MIN(res, ret);
// 		res = findauto(d + 1, a + 1, b + 1, r + h / 2, c + w / 2, h-h/2,w-w/2, mh, mw, ret & 0x3ff, ret >> 10);
// 		if (res == (1000 << 10) + 1000) {
// 			for (rint j = c; j <= c + w - mw && j < minw; ++j) {
// 				int fit = 0;

// 				rint i = r;
// 				for (i = r; i < r + mh && i < r + h; ++i) {
// 					fit += floor[i][j] == tc;
// 				}
// 				if (fit == 0) {
// 					bool find = true;
// 					for (rint ii = i - mh; ii < i; ++ii) {
// 						for (rint jj = j + 1; jj < j + mw; ++jj) {
// 							if (floor[ii][jj] == tc) {
// 								find = false;
// 								goto END;
// 							}
// 						}
// 					}
// 				END:
// 					if (find) {
// 						return (j << 10) + i - mh;
// 					}
// 				}
// 				while (i < r + h) {
// 					fit += (floor[i][j] == tc) - (floor[i - mh][j] == tc);
// 					++i;

// 					if (fit == 0) {
// 						bool find = true;
// 						for (rint ii = i - mh; ii < i; ++ii) {
// 							for (rint jj = j + 1; jj < j + mw; ++jj) {
// 								if (floor[ii][jj] == tc) {
// 									find = false;
// 									goto END2;
// 								}
// 							}
// 						}
// 					END2:
// 						if (find) {
// 							return (j << 10) + i - mh;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return ret;
// }

// int maketile(int d, int a, int b, int r, int c, int h, int w, int lx, int rx, int uy, int dy,int va) {
// 	a = a * 2 - 1;
// 	b = b * 2 - 1;
// 	if (lx < c) lx = c;
// 	if (lx >= c + w) lx = c + w;
// 	if (rx < c) rx = -1;
// 	if (rx > c + w) rx = c + w;
// 	if (uy >= r + h) uy = 0x3f3f3f3f;
// 	if (uy < r) uy = r;
	
// 	if (dy > r + h) dy = r + h;
// 	if (dy <= r) dy = -1;
// 	if (!h || !w) return 0;
// 	if (rx <= lx) return v[d][a][b];
// 	if (dy <= uy) return v[d][a][b];
// 	if (h == 1 && w == 1) {
// 		v[d][a][b] = va == -1 ? 0 : va;
// 		floor[r][c] = va == -1 ? 0 : tc;
// 		return floor[r][c] == tc;
// 	}
// 	v[d][a][b] = maketile(d + 1, a, b, r, c, h / 2, w / 2, lx, rx, uy, dy,va);
// 	v[d][a][b] += maketile(d + 1, a + 1, b, r + h / 2, c, h - h / 2, w / 2, lx, rx, uy, dy,va);
// 	v[d][a][b] += maketile(d + 1, a, b + 1, r, c + w / 2, h / 2, w - w / 2, lx, rx, uy, dy,va);
// 	v[d][a][b] += maketile(d + 1, a + 1, b + 1, r + h/2, c + w / 2, h-h / 2, w - w / 2, lx, rx, uy, dy,va);

// 	return v[d][a][b];
// }

int convtrie(int trie[TSIZE][26], char str[], int &tid) {
	int ret = 0;
	while (*str) {
		if (!trie[ret][conv[*str]]) {
			trie[ret][conv[*str]] = tid++;
		}
		ret = trie[ret][conv[*str]];
		str++;
	}
	return ret;
}

int mcheck(int r, int c, int h, int w) {
	int lx = c, rx = c + w;
	int uy = r, dy = r + h;
	for (rint i = 1; i < nid; ++i) {
		if (itemValid[i] != tc) continue;
		if (itemC[i] + itemW[i] <= lx || rx <= itemC[i] || itemR[i] + itemH[i] <= uy || dy <= itemR[i]) continue;
		return i;
	}
	return -1;
}

int findautopos(int h, int w){
    int fit = 0;
    if(h > R || w > C) return -1;
    for(rint i = 1; i <= R+1 - h; ++i){
        for(rint j = 1; j <= C+1-w; ++j){
            int ret = mcheck(i,j, h,w);
            if(ret == -1){
                return (j<<10) + i;
            }
        }
    }
    return -1;
}

int addItem(char name[], char tag[], int height, int width, int mode, int r, int c) {
	if (mode == 0 && (r < 1 || c < 1 || r + height > R + 1|| c + width > C+1)) 
		return 0;
	int n = convtrie(nnode, name, nid);
	int ta = convtrie(tnode, tag, tid);
	nlen[n] = 0;
	tlen[ta] = 0;
	while (*name) {
		mname[n][nlen[n]++] = *name++;
	}
	while (*tag) {
		mtag[ta][tlen[ta]++] = *tag++;
	}
	mname[n][nlen[n]] = 0;
	mtag[ta][tlen[ta]] = 0;
	itemT[n] = ta;
	itemH[n] = height;
	itemW[n] = width;

	if (mode == 1) {
		// int ret = findauto(0, 1, 1, 1, 1, R, C, height, width, 1000, 1000);
		// if (ret == (1000 << 10) + 1000) return 0;
		// r = ret & 0x3ff;
		// c = ret >> 10;
		// maketile(0, 1, 1, 1,1, R, C, c,c + width, r, r + height,1);
        int ret = findautopos(height, width);
        if(ret == -1) return 0;
        r = ret&0x3ff;
        c = ret>>10;
	}
	else {
		int block = mcheck(r, c, height, width);
		if (block != -1) return 0;
		// maketile(0, 1, 1, 1, 1, R, C, c, c + width, r, r + height,1);
	}
    for(rint i = r; i < r + height; ++i){
        for(rint j = c; j < c+width; ++j) floor[i][j] = tc;
    }
	itemValid[n] = tc;
	tS[ta] += height * width;
	itemR[n] = r;
	itemC[n] = c;
	tv[ta][tvsize[ta]++] = n;
    printf("add(%d %d)\n",r,c);
	
	return 1;
}

int removeItemByName(char name[]) {
	int n = convtrie(nnode, name, nid);
	if (itemValid[n] == tc) {
		// maketile(0, 1, 1, 1, 1, R, C, itemC[n], itemC[n] + itemW[n], itemR[n], itemR[n] + itemH[n], -1);
        rint rr = itemR[n] + itemH[n];
        rint cc = itemC[n] + itemW[n];
        for(rint i = itemR[n]; i < rr; ++i ){                
            for(rint j = itemC[n]; j < cc; ++j){
                floor[i][j] = 0;
            }
        }
		itemValid[n] = 0;
		tS[itemT[n]] -= itemW[n] * itemH[n];
		return 1;
	}
	return 0;
}

int removeItemByTag(char tag[]) {
	int t = convtrie(tnode, tag, tid);
	int ret = 0;
	for (rint i = 0; i < tvsize[t]; ++i) {
		int n = tv[t][i];
		if (itemValid[n] != tc) continue;
		itemValid[n] = 0;
		ret++;
		// maketile(0, 1, 1, 1, 1, R, C, itemC[n], itemC[n] + itemW[n], itemR[n], itemR[n] + itemH[n], -1);
        rint rr = itemR[n] + itemH[n];
        rint cc = itemC[n] + itemW[n];
        for(rint i = itemR[n]; i < rr; ++i ) {                
            for(rint j = itemC[n]; j < cc; ++j) {
                floor[i][j] = 0;
            }
        }
	}
	tvsize[t] = 0;
	tS[t] = 0;

	return ret;
}

int getItem(int r, int c, char name[], char tag[]) {
	int n = mcheck(r, c, 1, 1);
	if (n == -1) return 0;
	for (rint i = 0; i < nlen[n]; ++i) {
		name[i] = mname[n][i];
	}
	int t = itemT[n];
	for (rint i = 0; i < tlen[t]; ++i) {
		tag[i] = mtag[t][i];
	}
	name[nlen[n]] = 0;
	tag[tlen[t]] = 0;
	return 1;
}

int getArea(char tag[]) {
	return tS[convtrie(tnode, tag, tid)];
}