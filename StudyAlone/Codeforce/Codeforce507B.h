#pragma once
#include<cstdio>

int n, m;
bool check[1001];
int top = 0;
int que[100000];

int Codeforce507B() {
	scanf("%d %d\n", &n, &m);
	int num = 1 + 2 * m;
	int now = m+1;
	int f, r;
	f = r = 0;
	while (true) {
		if (now <= n) {
			que[r++] = now;
			now +=  2*m + 1;
		}
		else {
			que[r++] = now;
			break;
		}
	}



	int conv = 0;
	if (r > 1 && que[r - 2] + m == n) {
		r--;
	}
	else {
		conv = que[r - 1] - n;
	}

	printf("%d\n", que[0] - conv < 0 ? --r : r);
	if (que[0] - conv < 0) conv = 0;
	
	while (f!=r) {
		printf("%d ", que[f++] - conv);
	}
	return 0;
}