#pragma once
#include<cstdio>

int n, k;

char str[51];
int kmp[51];
int last;

char resRes[1000000];
int reslen;
int setLast() {
	int prev = 0;
	kmp[0] = -1;
	int j =0;

	for (int i = 1; i < n; i++) {
		kmp[i] = j;
		while (j != -1 && str[j] != str[i]) {
			j = kmp[j];
		}
		j++;
	}
	kmp[n-1] = str[kmp[n - 1]] == str[n - 1] ? kmp[n - 1] + 1  : str[0] == str[n-1];

	return kmp[n-1];
}

int Codeforce506A() {
	scanf("%d %d\n", &n, &k);
	scanf("%s\n", str);
	int idx = n == 1 ? 0 :setLast();

	char res[51];
	int rlen = 0;
	for (int i = 0; i < n - idx; i++) {
		res[i] = str[i + idx];
	}

	for (int i = 0; i < n; i++) resRes[reslen++] = str[i];
	k--;
	while (k--) {
		for (int i = 0; i < n - idx; i++)
			resRes[reslen++] = res[i];
	}

	resRes[reslen] = 0;
	printf("%s\n", resRes);

	return 0;
}