#pragma once
#include<cstdio>

int arr[200010];

int Codeforce506B() {
	int n;
	int l = 0;
	arr[0] = -1;
	scanf("%d\n", &n);
	int in;
	scanf("%d\n", &in);

	arr[1] = in;
	l = 1;
	int max = 1;
	for (int i = 1; i < n; i++) {
		int in;
		scanf("%d\n", &in);

		if (arr[l] * 2 >= in) {
			l++;
			arr[l] = in;
			max = max < l ? l : max;
		}
		else {
			l = 1;
			arr[1] = in;
		}
	}
	printf("%d\n", max);
	return 0;
}