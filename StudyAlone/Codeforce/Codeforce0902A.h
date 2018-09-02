#pragma once
#include<cstdio>
#include<vector>

using namespace std;
int getLog(int n) {
	int res = 0;
	while (n) {
		res++;
		n >>= 1;
	}
	return res;
}
int Codeforce0902A() {
	int n;
	scanf("%d\n", &n);
	printf("%d\n", getLog(n));

	return 0;
}