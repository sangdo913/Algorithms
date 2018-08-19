#pragma once
#include<cstdio>
#include<string>
#include<string.h>

using namespace std;

char str[2][300000];
int n, m;

bool find(int p) {
	for (int i = p; i < m; i++) {
		if (strcmp(str[0] + p+1, str[1] + i) == 0) return true;
	}
	return false;
}

int Codeforce50401() {
	
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