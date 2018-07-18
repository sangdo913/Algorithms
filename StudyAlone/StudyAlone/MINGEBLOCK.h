#pragma once
#include<cstdio>
#include<cstring>

int n, m, q;
char map[30][31];
char insert[31];

void DOWN() {
	char st[30];
	for (int i = 0; i < m; i++) {
		int f;
		int p = 0;
		for (f = 0; f < n; f++) {
			if (map[f][i] != '#') {
				st[p++] = map[f][i];
				map[f][i] = '#';
			}
		}

		while (p) {
			map[--f][i] = st[--p];
		}
	}
}

void U() {
	bool check = true;
	for (int i = 0; i < m; i++) {
		check = map[0][i] == '#';
		if (check == false) break;
	}

	if (check == false) return;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = map[i + 1][j];
		}
	}
	for (int i = 0; i < m; i++) {
		map[n - 1][i] = insert[i];
	}
	DOWN();
}

void R() {
	char st[30];
	for (int i = 0; i < n; i++) {
		int f;
		int p = 0;
		for (f = 0; f < m; f++) {
			if (map[i][f] != '#') {
				st[p++] = map[i][f];
				map[i][f] = '#';
			}
		}

		while (p) {
			map[i][--f] = st[--p];
		}
	}
}
void L() {
	char st[30];
	for (int i = 0; i < n; i++) {
		int f;
		int p = 0;
		for (f = m-1; f >= 0; f--) {
			if (map[i][f] != '#') {
				st[p++] = map[i][f];
				map[i][f] = '#';
			}
		}

		while (p) {
			map[i][++f] = st[--p];
		}
	}
}

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void D() {
	int queue[900][2];
	int f, r;
	
	int store[900][2];
	int temp[900][2];
	int len = 0, tempLen;
	int maxSize = 0;
	bool visit[30][30] = { false };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visit[i][j]) continue;
			if (map[i][j] == '#') continue;

			char col = map[i][j];
			f = r = 0;
			int size = 0;
			queue[r][0] = i;
			queue[r++][1] = j;
			visit[i][j] = true;
			tempLen = 0;
			while (f != r) {
				int nr = queue[f][0];
				int nc = queue[f++][1];
				size++;

				temp[tempLen][0] = nr;
				temp[tempLen++][1] = nc;

				for (int d = 0; d < 4; d++) {
					int nnr = nr + dr[d];
					int nnc = nc + dc[d];

					if (nnr >= 0 && nnr < n && nnc >= 0 && nnc < m)
					{
						if (visit[nnr][nnc]) continue;
						if (map[nnr][nnc] != col) continue;

						visit[nnr][nnc] = true;
						queue[r][0] = nnr;
						queue[r++][1] = nnc;
					}
				}
			}
			if (size > maxSize) {
				maxSize = size;
				len = 0;
				for (int i = 0; i < tempLen; i++) {
					store[len][0] = temp[i][0];
					store[len++][1] = temp[i][1];
				}
			}
			else if (size == maxSize) {
				for (int i = 0; i < tempLen; i++) {
					store[len][0] = temp[i][0];
					store[len++][1] = temp[i][1];
				}
			}
		}
	}

	for (int i = 0; i < len; i++) {
		map[store[i][0]][store[i][1]] = '#';
	}
	DOWN();
}


int MINGEBLOCK() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d\n", &n, &m, &q);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c\n", &map[i][j]);
			}
		}

		for (int i = 0; i < q; i++) {
			char Q;
			scanf("%c\n", &Q);

			switch (Q) {
			case 'D':
				D(); break;
			case'L':
				L(); break;
			case 'R':
				R(); break;
			case 'U':
				scanf(" %s\n", &insert);
				U(); break;
			}
		}

		printf("#%d\n", tc);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%c", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
