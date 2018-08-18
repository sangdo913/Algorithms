#pragma once
#include<cstdio>

char res[2][21][21][21][21];
char path[2][21][21][21][21];
char que[20 * 20 * 20 * 20][6];

int CodeBattle081401() {
	int t;
	scanf("%d\n", &t);
	
	int f = 0, r = 0;
	
	que[r][0] = 1;
	que[r][1] = 0;
	que[r][2] = 0;
	que[r][3] = 0;
	que[r][4] = '0';
	que[r++][5] = 1;

	que[r][0] = 0;
	que[r][1] = 1;
	que[r][2] = 0;
	que[r][3] = 0;
	que[r][4] = '1';
	que[r++][5] = 2;

	que[r][0] = 0;
	que[r][1] = 0;
	que[r][2] = 1;
	que[r][3] = 0;
	que[r][4] = '0';
	que[r++][5] = 3;

	que[r][0] = 0;
	que[r][1] = 0;
	que[r][2] = 0;
	que[r][3] = 1;
	que[r][4] = '1';
	que[r++][5] = 4;

	res[0][1][0][0][0] = '0';
	res[0][0][1][0][0] = '1';
	res[0][0][0][1][0] = '0';
	res[0][0][0][0][1] = '1';
	res[1][1][0][0][0] = '0';
	res[1][0][1][0][0] = '0';
	res[1][0][0][1][0] = '1';
	res[1][0][0][0][1] = '1';

	while (f != r) {
		int now[6] = { que[f][0], que[f][1], que[f][2], que[f][3], que[f][4], que[f][5] };
		f++;


		if (now[4] =='0') {
			if (now[0] != 20 && res[0][now[0] + 1][now[1]][now[2]][now[3]] == 0) {
				res[0][now[0] + 1][now[1]][now[2]][now[3]] = '0';
				path[0][now[0] + 1][now[1]][now[2]][now[3]] = 1;
				que[r][0] = now[0]+1;
				que[r][1] = now[1];
				que[r][2] = now[2];
				que[r][3] = now[3];
				que[r][4] = '0';
				que[r++][5] = 1; 
			}

			if (now[1] != 20 && res[1][now[0]][now[1]+1][now[2]][now[3]] == 0) {
				res[1][now[0]][now[1]+1][now[2]][now[3]] = '1';
				path[1][now[0]][now[1]+1][now[2]][now[3]] = 2;
				que[r][0] = now[0];
				que[r][1] = now[1]+1;
				que[r][2] = now[2];
				que[r][3] = now[3];
				que[r][4] = '1';
				que[r++][5] = 2;
			}
		}

		if (now[4] =='1') {
			if (now[2] != 20 && res[0][now[0]][now[1]][now[2]+1][now[3]] == 0) {
				res[0][now[0]][now[1]][now[2]+1][now[3]] = '0';
				path[0][now[0]][now[1]][now[2]+1][now[3]] = 3;
				que[r][0] = now[0];
				que[r][1] = now[1];
				que[r][2] = now[2] + 1;
				que[r][3] = now[3];
				que[r][4] = '0';
				que[r++][5] = 3;
			}

			if (now[3] != 20 && res[1][now[0]][now[1]][now[2]][now[3]+1]==0) {
				res[1][now[0]][now[1]][now[2]][now[3]+1] = '1';
				path[1][now[0]][now[1]][now[2]][now[3]+1] = 4;
				que[r][0] = now[0];
				que[r][1] = now[1];
				que[r][2] = now[2];
				que[r][3] = now[3] + 1;
				que[r][4] = '1';
				que[r++][5] = 4;
			}
		}
	}

	for (int tc = 1; tc <= t; tc++) {
		char rc[100];
		int len = 0;
		rc[0] = 0;
		int cmp[5];

		scanf("%d %d %d %d\n", &cmp[1], &cmp[2], &cmp[3], &cmp[4]);
		
		int now = -1;
		now = res[0][cmp[1]][cmp[2]][cmp[3]][cmp[4]] < res[1][cmp[1]][cmp[2]][cmp[3]][cmp[4]] ? res[1][cmp[1]][cmp[2]][cmp[3]][cmp[4]] : res[0][cmp[1]][cmp[2]][cmp[3]][cmp[4]];

		if (now == 0) {
			printf("#%d impossible\n", tc);
			continue;
		}

		now -= '0';
		while (cmp[1] + cmp[2] + cmp[3] + cmp[4] != 1) {
			rc[++len] = res[now][cmp[1]][cmp[2]][cmp[3]][cmp[4]];
			int temp = now;
			now =path[now][cmp[1]][cmp[2]][cmp[3]][cmp[4]] > 2 ;
			cmp[path[temp][cmp[1]][cmp[2]][cmp[3]][cmp[4]]]--;
		}

		rc[++len] = res[0][cmp[1]][cmp[2]][cmp[3]][cmp[4]];
		rc[++len] = res[1][cmp[1]][cmp[2]][cmp[3]][cmp[4]];
		printf("#%d ", tc);
		for (int i = len; i > 0; i--) {
			printf("%c", rc[i]);
		}
		printf("\n");
	}

	return 0;
}