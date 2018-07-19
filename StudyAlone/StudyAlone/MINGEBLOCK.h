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
	// 행에 빈공간이 없는지 체크
	for (int i = 0; i < m; i++) {
		check = map[0][i] == '#';
		if (check == false) break;
	}

	// 빈공간이 없으면 아무 일도 하지 않음
	if (check == false) return;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = map[i + 1][j];
		}
	}
	for (int i = 0; i < m; i++) {
		map[n - 1][i] = insert[i];
	}
	//아래로 밀어줌
	DOWN();
}

void R() {
	char st[30];						//스택을 이용해서 오른쪽으로 밀어줌
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
	
	int store[900][2];													// 삭제되어야할 블록들 저장
	int temp[900][2];													// 한 영역의 블록 저장
	int len = 0, tempLen;												// len : store의 크기, tempLen : temp의 크기
	int maxSize = 0;
	bool visit[30][30] = { false };										// 처리했는지 체크

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visit[i][j]) continue;									// 이미 처리된 블록이면 처리할 필요가 없다.
			if (map[i][j] == '#') continue;								// 빈공간이면 처리할 필요가 없다.

			char col = map[i][j];										// 블록의 색 저장
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

					if (nnr >= 0 && nnr < n && nnc >= 0 && nnc < m)		// 블록이 맵 사이즈 안에 있어야 한다.
					{
						if (visit[nnr][nnc]) continue;		
						if (map[nnr][nnc] != col) continue;				// 색이 같은 블록만 처리한다.

						visit[nnr][nnc] = true;
						queue[r][0] = nnr;								// 색이 같은 블럭이면 같은 영역으로 간주해 큐에 넣는다.
						queue[r++][1] = nnc;
					}
				}
			}
			if (size > maxSize) {										// 현재 영역의 사이즈가 최대 영역보다 큰 경우 사이즈를 갱신하고,
				maxSize = size;											// 이전의 값들은 모두 버린다.
				len = 0;
				for (int i = 0; i < tempLen; i++) {
					store[len][0] = temp[i][0];
					store[len++][1] = temp[i][1];
				}
			}
			else if (size == maxSize) {									// 현재 영역의 사이즈가 최대 영역과 같을 경우
				for (int i = 0; i < tempLen; i++) {						// 삭제할 영역을 보관하는 store 뒤에 블록들을 이어붙인다.
					store[len][0] = temp[i][0];
					store[len++][1] = temp[i][1];
				}
			}
		}
	}

	for (int i = 0; i < len; i++) {								
		map[store[i][0]][store[i][1]] = '#';							//블록을 삭제한다.
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
