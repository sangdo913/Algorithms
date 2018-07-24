#pragma once
#include<cstdio>
//https://www.swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AWS2dSgKA8MDFAVT&categoryId=AWSqtLN6BhMDFAW0&categoryType=BATTLE

char str[1002];

int GoodPerformanceProject(){
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%s\n", str);

		int people = str[0]-'0', hire = 0;
		for (int i = 1; str[i]; i++) {
			hire += people + hire < i? i  - people - hire : 0;
			people += str[i] - '0';
		}
		printf("#%d %d\n", tc, hire);
	}
	return 0;
}