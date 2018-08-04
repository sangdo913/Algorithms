//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWTaTDua3OoDFAVT&categoryId=AWTaTDua3OoDFAVT&categoryType=CODE
#pragma once
#include<cstdio>

int SWExpert5162() {
	register int a[2], c, t;
	scanf("%d\n", &t);

	for (register int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d\n", &a[0], &a[1], &c);
		register int idx = a[0] > a[1];
		printf("%d %d\n", tc, c / a[idx]);
	}
	
	return 0;
}