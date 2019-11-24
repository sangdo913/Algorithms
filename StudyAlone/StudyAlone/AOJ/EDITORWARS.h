#include<stdio.h>
#include<vector>
#include<iostream>
char str[4];

int ack[10000];
int opposite[10000];
using namespace std;
int getp(int i) {
	if (ack[i] < 0) return i;
	return ack[i] = getp(ack[i]);
}

void join(int a, int b) {
	int pa = getp(a), pb = getp(b);

	if (pa == pb) return;
	
	if (ack[pa] < ack[pb]) {
		pa ^= pb ^= pa ^= pb;
	}

	ack[pb] += ack[pa];
	ack[pa] = pb;
}

int visit[10000];
int query[100000][2];
int qid;
int main() {
	int tc;
	int n, m;
	scanf("%d", &tc);

	for (int t = 1; t <= tc; ++t) {
		int a, b;
		scanf("%d %d", &n, &m);
		int valid = 0;
		int invalidpos = 0x3f3f3f3f;

		for (int j = 0; j < n; ++j) opposite[j] = ack[j] = -1; 

		int j;
		for (j = 1; j <= m; ++j) {
			scanf("%s %d %d", str, &a,  &b);
			
			if (str[0] == 'A') {
				int pa = getp(a), pb = getp(b);
				if (opposite[pa] != -1 && (getp(opposite[pa]) == pb)){
					invalidpos = j < invalidpos ? j : invalidpos;
				}
				else if (opposite[pb] != -1 && pa == getp(opposite[pb])) {
					invalidpos = j < invalidpos ? j : invalidpos;
				}

				if (opposite[pa] != -1 || opposite[pb] != -1) {
					if (opposite[pa] == -1) opposite[pa] = opposite[pb];
					else if (opposite[pb] == -1) opposite[pb] = opposite[pa];
					join(opposite[pa], opposite[pb]);
				}

				join(a, b);
			}
			else {
				int pa = getp(a), pb = getp(b);
				if (pa == pb) {
					invalidpos = j < invalidpos ? j : invalidpos;
				}
				if (opposite[pa] != -1) {
					join(opposite[pa], pb);
				}
				if (opposite[pb] != -1) {
					join(opposite[pb], pa);
				}
				opposite[pa] = pb;
				opposite[pb] = pa;
			}
		}

		if (invalidpos == 0x3f3f3f3f) {
			int mmin = 0;
			for (int i = 0; i < n; ++i) {
				if (opposite[i] != -1) {
					int o = getp(opposite[i]);
					int pi = getp(i);
					if (visit[o] != t && visit[pi] != t ) {
						visit[pi] = visit[o] = t;
						if (ack[pi] < ack[o]) {
							pi ^= o ^= pi ^= o;
						}
						mmin -= ack[pi];
					}
				}
			}
			printf("MAX PARTY SIZE IS %d\n", n-mmin);
		}
		else {
			printf("CONTRADICTION AT %d\n", invalidpos);
		}

	}
	return 0;
}