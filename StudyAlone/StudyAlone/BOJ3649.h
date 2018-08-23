// https://www.acmicpc.net/problem/3649
// 로봇 프로젝트

#pragma once
#include<cstdio>
#include<cstring>
char check[100000010];

int BOJ3649() {
	int x;

	while (scanf("%d\n", &x) != EOF) {
		x *= 10000000;
		int res = 0x7fffffff;
		int n;

		memset(check, 0, sizeof(check));
		
		scanf("%d\n", &n);
		while (n--) {
			int in;
			scanf("%d\n", &in);

			if (in < x) {
				if (x - in <= 100000000 && check[x - in]) {
					int temp = in < x - in ? in : x - in;
					res = res < temp ? res : temp;
				}

				check[in]++;
				check[in] = check[in] > 2 ? 2 : check[in];
			}
		}

		if (res == 0x7fffffff) printf("danger\n");
		else printf("yes %d %d\n", res , x - res);
	}
	return 0;
}