//https://codeforces.com/contest/1025/problem/C
//Plasticine zebra
#pragma once
#include<cstdio>
#include<cstring>
int len;
char str[2][200001];

int Codeforce0819C() {
	scanf("%s\n", str[0]);
	len = strlen(str[0]);

	for (int i = 0; i < len; i++) {
		str[1][i] = str[0][len - 1 - i];
		str[0][len + i] = str[0][i];
		str[1][len + i] = str[1][i];
	}

	char st[2] = { str[0][0], str[1][0] };
	int cnt[2] = { 1,1 };
	int res[2] = { 1,1 };
	for (int i = 1; i < 2 * len; i++) {
		if (st[0] != str[0][i]) {
			cnt[0]++;
			res[0] = res[0] < cnt[0] ? cnt[0] : res[0];
		}
		else { cnt[0] = 1; }
		st[0] = str[0][i];
		if (st[1] != str[1][i]) {
			cnt[1]++;
			res[1] = res[1] < cnt[1] ? cnt[1] : res[1];
		}
		else { cnt[1] = 1; }
		st[1] = str[1][i];
	}
	res[0] = res[0] > len ? len : res[0];
	res[1] = res[1] > len ? len : res[1];
	printf("%d\n", res[0] < res[1] ? res[1] : res[0]);
	return 0;	
}