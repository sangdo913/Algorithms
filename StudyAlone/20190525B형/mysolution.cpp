#define MAXIMAGESIZE 1000
#define MAXSAMPLESIZE 50
#define TABLESIZE 2000017

typedef unsigned int ui;

struct NODE {
	ui key;
	int r[2], c[2];
	NODE* prev, *next;
}nodes[1000000];

NODE head[TABLESIZE];

unsigned char waper[2000][2000];
unsigned char *sample;
int n, m;

struct Detect {
	int height, width;
};
int idx = 0;
int cnt;
#include<stdio.h>
void init(int N, int M) 
{
	cnt = 0;
	idx = 0;
	for (register int i = 0; i < TABLESIZE; ++i) head[i].prev = head[i].next = &head[i];
	n = N, m = M;
}

void goodImage(unsigned char image[][MAXIMAGESIZE]) 
{
	for (int sr = 0; sr < n + m; sr+=n) {
		for (int sc = 0; sc < n + m; sc+=n) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					waper[sr + i][sc + j] = image[i][j];
				}
			}
		}
	}

	ui key = 0;

	for (int i = 0; i < n; ++i) {
		key = 0;
		key = ((ui)waper[i][0] << 8) + waper[i + 1][0];

		for (int j = 0; j < n; ++j) {
			key = (key << 16) + ((ui)waper[i][j + 1] << 8) + waper[i + 1][j + 1];
			NODE& nn = nodes[idx++];
			ui hash = key % TABLESIZE;
			nn.key = key;

			for (int d = 0; d < 2; d++) {
				nn.r[d] = (n + i -4 * d)%n;
				nn.c[d] = (n+ j -4 * d)%n;
			}

			nn.next = head[hash].next;
			nn.prev = &head[hash];

			head[hash].next->prev = &nn;
			head[hash].next = &nn;
		}
		
	}
}
int query;
int visit[50][50];
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x)<(y) ? (x) : (y))

Detect check(unsigned char sample[][MAXSAMPLESIZE], int r, int c) {
	query++;
	bool find = false;
	Detect ret = { 0,0 };

	int maxx, maxy, minx, miny;
	maxx = maxy = -0x3f3f3f3f;
	minx = miny = 0x3f3f3f3f;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (sample[i][j] != waper[r + i][c + j]) {
				maxx = MAX(j, maxx);
				minx = MIN(j, minx);
				maxy = MAX(i, maxy);
				miny = MIN(i, miny);
			}
		}
	}

	if (minx == 0x3f3f3f3f) return { 0,0 };

	ret.height = maxy - miny + 1;
	ret.width = maxx - minx + 1;

	if (ret.height> 3 || ret.width > 3) return{ -1,-1 };

	for (int i = miny; i <= maxy; ++i) {
		for (int j = minx; j <= maxx; ++j) {
			if (sample[i][j] == waper[r + i][j + c]) return { -1,-1 };
		}
	}
	return ret;
}

#include<stdio.h>
Detect sampleImage(unsigned char sample[][MAXSAMPLESIZE]) 
{
	Detect dt;
	const int dr[] = { 0,1,0,1 };
	const int dc[] = { 0,0,1,1 };

	for (int i = 0; i < 2; ++i) {
		ui key = 0;
		int r = 4*i;
		int c = 4*i;
		for (int d = 0; d < 4; d++) {
			key <<= 8;
			key += sample[r + dr[d]][c + dc[d]];
		}
		ui hash = key % TABLESIZE;
		NODE* cur = head[hash].next;

		while (cur != &head[hash]) {
			if (cur->key == key && cur->r[i] >= 0 && cur->c[i] >= 0) {
				dt = check(sample, cur->r[i], cur->c[i]);
				if (dt.width != -1) return dt;
			}
			
			cur = cur->next;
		}
	}

	return { -1,-1 };
}
