#pragma once
#include<cstdio>
#include<cstring>

char str[51];
char res[5][502];


void draw(int r, int c) {
	res[r - 2][c] = res[r - 1][c - 1] = res[r - 1][c + 1] = res[r][c - 2] = res[r][c + 2] = res[r + 1][c - 1] = res[r + 1][c + 1] = res[r + 2][c] = '#';
}

int len() {
	int i = 0;
	while (str[i]) i++;
	return i;
}
int DasolDiamondDecoration() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%s\n", str);
		memset(res, '.', sizeof(res));

		int l = len();

		for (int i = 0, st = 2; i < l; i++, st += 4) {
			res[2][st] = str[i];
			draw(2, st);
		}
		for (int i = 0; i < 5; i++) res[i][4 * l + 1] = 0;
		for (int i = 0; i < 5; i++) {
			printf("%s\n",res[i]);
		}
	}

	return 0;
}