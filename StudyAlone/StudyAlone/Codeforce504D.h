#pragma once
#include<cstdio>

int info[200001][2], arr[200001], make[200001];
int sta[200001], top;


int Codeforce504D() {
	int n, q;
	scanf("%d %d\n", &n, &q);
	bool has0 = false, hasQ = false;
	
	for (int i = 1; i <= n; i++) {
		scanf("%d \n", &arr[i]);
		info[arr[i]][0] = info[arr[i]][0] ? info[arr[i]][0] : i;
		info[arr[i]][1] = i;
		has0 |= arr[i] == 0;
		hasQ |= arr[i] == q;
	}

	if (!has0 && !hasQ) { printf("NO\n"); return 0; }

	if (!hasQ) {
		int i = 1;
		while (arr[i]) i++;
		info[q][1] = info[q][0] = i;
	}

	for (int i = 1; i <= q; i++) {
		make[info[i][0]] = i;
		make[info[i][1]] = i;
	}

	info[1][0] = 1;
	info[1][1] = n;

	make[1] = make[1] ? make[1] : 1;
	int now = make[1];
	for (int i = 2; i <= n; i++) {
		if (info[now][1] < i) {
			now = 0;
			while (top) {
				now = sta[--top];
				if (info[now][1] > i) break;
				now = 0;
			}
			now = now ? now : 1;
		}
		if (now < make[i]) {
			sta[top++] = now;
			now = make[i];
		}

		make[i] = now;
	}
	for (int i = 1; i <= n; i++) {
		if (arr[i] == 0) continue;
		if (arr[i] != make[i]) { printf("NO\n"); return 0; }
	}
	printf("YES\n");
	for (int i = 1; i <= n; i++) printf("%d ", make[i] ? make[i] : 1);
	return 0;
}