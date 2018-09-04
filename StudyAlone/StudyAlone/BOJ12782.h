//https://www.acmicpc.net/problem/12782
//비트 우정 지수

#pragma once
#include<cstdio>
#include<cstring>

int n;
char str[2][1000001];

int BOJ12782() {
	scanf("%d\n", &n);

	while (n--) {
		scanf("%s %s\n", str[0], str[1]);

		int len = strlen(str[0]);

		int nums[256] = { 0 };
		for (int i = 0; i < len; i++) {
			if (str[0][i] != str[1][i]) {
				nums[str[0][i]] ++;
			}
		}

		printf("%d\n", nums['0'] < nums['1'] ? nums['1'] : nums['0']);
	}
	return 0;
}
