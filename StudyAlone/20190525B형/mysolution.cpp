#define MAXIMAGESIZE 1000
#define MAXSAMPLESIZE 50
#define TABLESIZE 2000013

typedef unsigned long long ull;

struct NODE {
	ull key;
	int r, c;
	NODE* prev, *next;
}nodes[4000000];

NODE head[TABLESIZE];
NODE head2[TABLESIZE];

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
	//printf("max cnt : %4d\n", cnt);
	cnt = 0;
	idx = 0;
	for (register int i = 0; i < TABLESIZE; ++i) head[i].prev = head[i].next = &head[i], head2[i].prev = head2[i].next = &head2[i];
	n = N, m = M;
}

void goodImage(unsigned char image[][MAXIMAGESIZE]) 
{
	//int sr[] = { 0,0,n,n };
	//int sc[] = { 0,n,0,n };

	for (int sr = 0; sr < n + m; sr+=n) {
		for (int sc = 0; sc < n + m; sc+=n) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					waper[sr + i][sc + j] = image[i][j];
				}
			}
		}
	}
	//for (int d = 0; d < 4; ++d) {
	//	for (int i = 0; i < n; ++i) {
	//		for (int j = 0; j < n; ++j) {
	//			waper[sr[d] + i][sc[d] + j] = image[i][j];
	//		}
	//	}
	//}

	ull key = 0, key2 = 0;

	for (int i = 0; i < n; ++i) {
		key = 0;
		key2 = 0;
		
		for (int ii = 0; ii < 3; ++ii) {
			key <<= 8; key += waper[i][ii];
			key <<= 8; key += waper[i + 1][ii];

			key2 <<= 8; key2 += waper[i+4][ii];
			key2 <<= 8; key2 += waper[i + 5][ii];
		}
		
		for (int j = 0; j < n; ++j) {
			key <<= 8;
			key += waper[i][j + 3];
			key <<= 8;
			key += waper[i + 1][j + 3];

			key2 <<= 8;
			key2 += waper[i + 4][j + 3];

			key2 <<= 8;
			key2 += waper[i + 5][j + 3];
			int k = key % TABLESIZE;
			int k2 = key2 % TABLESIZE;

			NODE& node = nodes[idx++];
			node.r = i; node.c = j;
			node.key = key;
			node.next = head[k].next;
			node.prev = &head[k];
			head[k].next->prev = &node;
			head[k].next = &node;

			NODE& node2 = nodes[idx++];
			node2.r = i; node2.c = j;
			node2.key = key2;
			node2.next = head2[k2].next;
			node2.prev = &head2[k2];
			head2[k2].next->prev = &node2;
			head2[k2].next = &node2;
		}
	}
}
int query;
int visit[50][50];

Detect check(unsigned char sample[][MAXSAMPLESIZE], int r, int c) {
	query++;
	bool find = false;
	Detect ret = { 0,0 };
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (sample[i][j] != waper[r + i][c + j]) {
				if (find&& visit[i][j] !=query) 
					return { -1,-1 };
				else {
					if (visit[i][j] == query) continue;
					find = true;
					int height = 0, width = 0;
					while (j+width < m && sample[i][j + width] != waper[r + i][j + c + width])width++;
					while (i +  height < m && sample[i + height][j] != waper[r + i + height][j + c])height++;
					if (width > 3 || height > 3) return { -1,-1 };
					bool check = true;

					for (int ii = 0; ii < height; ++ii) {
						for (int jj = 0; jj < width; ++jj) {
							visit[i + ii][j + jj] = query;
							if (sample[i + ii][jj + j] == waper[r + i + ii][j + c + jj]) {
								check = false; goto LOOPEND;
							}
						}
					}
					LOOPEND:
					if (!check) {
						return { -1,-1 };
					}
					ret.height = height;
					ret.width = width;
				}
			}
		}
	}
	return ret;
}

#include<stdio.h>
Detect sampleImage(unsigned char sample[][MAXSAMPLESIZE]) 
{
	Detect dt;
	ull key = 0, key2 = 0;
	for (int i = 0; i < 4; ++i) {
		key <<= 8;
		key += sample[0][i];
		key <<= 8;
		key += sample[1][i];
		key2 <<= 8;
		key2 += sample[4][i];
		key2 <<= 8;
		key2 += sample[5][i];
	}

	int k = key % TABLESIZE;
	
	NODE* cur = head[k].next;
	while (cur != &head[k]) {
		//cnt++;
		dt = check(sample, cur->r, cur->c);
		if (dt.width != -1 && dt.width != -1) {
			return dt;
		}
		cur = cur->next;
	}

	k = key2 % TABLESIZE;
	cur = head2[k].next;

	while (cur != &head2[k]) {
	//	++cnt;
		dt = check(sample, cur->r, cur->c);
		if (dt.width != -1 && dt.width != -1) {
			return dt;
		}
		cur = cur->next;
	}

	return { -1,-1 };
}
