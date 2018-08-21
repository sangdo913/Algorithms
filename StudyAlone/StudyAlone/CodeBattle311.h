//https://www.swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AWVWgkP6sQ0DFAUO&categoryId=AWVBkD86xbkDFAVZ&categoryType=BATTLE
// 의석이의 세로로 말해요
#pragma once
#include<cstdio>
#include<cstring>

char in[5][16]; int ilen[5];
char res[76];
int rlen;

int CodeBattle311() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		rlen = 0;
		for (int i = 0; i < 5; i++) {
			scanf("%s\n", in[i]);
			ilen[i] = strlen(in[i]);
		}

		for (int j = 0; j < 15; j++) {
			for (int i = 0; i < 5; i++) {
				if (ilen[i] > j) {
					res[rlen++] = in[i][j];
				}
			}
		}

		res[rlen] = 0;
		printf("%s\n", res);
	}
	return 0;
}