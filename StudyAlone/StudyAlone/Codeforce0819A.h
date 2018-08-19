#pragma once
#include<cstdio>
int nums[256];
int Codeforce0819A() {
	int n;
	scanf("%d\n", &n);
	if (n == 1) {
		printf("Yes\n");
		return 0;
	}
	bool res = false;
	for (int i = 0; i < n; i++) {
		char a;
		scanf("%c\n", &a);
		nums[a]++;
		if (nums[a] == 2)
		{
			res = true;
		}
	}
	res ? printf("Yes\n") : printf("No\n");
	return 0;
}