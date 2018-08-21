#pragma once
#include<cstdio>
char str[200001], res[200001];
int len, rlen;


int Codeforce504C() {
	int m, n;
	scanf("%d %d\n", &m, &n);

	scanf("%s\n", str);

	res[rlen++] = str[len++];
	int cnt = 0, idx = (m-n)/2;
	while(cnt != idx) {
		res[rlen++] = str[len++];
		if (res[rlen - 1] == ')' && res[rlen - 2] == '(') {
			cnt++;
			rlen -= 2;
		}
	}
	while (len != m) res[rlen++] = str[len++];
	res[rlen] = 0;
	printf("%s\n", res);
	return 0;
}