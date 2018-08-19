﻿#pragma once
#include<cstdio>
#include<string>
#include<string.h>

using namespace std;

char str[2][300000];
int n, m;

bool find(int p) {
	int pos = m - (n - p - 1);
	if (pos < p) return false;
	return (strcmp(str[0] + p + 1, str[1] + pos) == 0);
}

int main() {

	scanf("%d %d\n", &n, &m);
	scanf("%s\n%s\n", str[0], str[1]);
	bool res = true;
	int i = 0;
	while (true) {
		if (str[0][i] == '*') {
			res = find(i);
			break;
		}

		else if (str[0][i] != str[1][i]) {
			res = false;
			break;
		}
		else if (str[0][i] == 0 && str[1][i] == 0) {
			res = true; break;
		}
		i++;
	}

	if (res) { printf("YES\n"); }
	else { printf("NO\n"); }

	return 0;
}