#pragma once
#include<cstdio>
#include<cstring>
int direct[200001];
int cost[200001];
int inorder[200001];
int que[200001], f, r;
int groups[200001];
int gc[200001];

int Codeforce0818D() {
	int n;
	scanf("%d\n", &n);
	memset(gc, 0x3f, sizeof(gc));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cost[i]);
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d\n", &direct[i]);
		inorder[direct[i]]++;
	}

	for (int i = 1; i <= n; i++) {
		if (inorder[i] == 0) que[r++] = i;
	}

	while (f != r) {
		int now = que[f++];

		inorder[direct[now]]--;
		if (inorder[direct[now]] == 0) que[r++] = direct[now];
	}

	f = r = 0;

	int g = 0;

	for (int i = 1; i <= n; i++) {
		if (groups[i] != 0) continue;
		if (inorder[i] == 0) continue;
		int now = i;

		groups[i] = ++g;
		while (groups[direct[now]] == 0) {
			groups[direct[now]] = g;
			now = direct[now];
		}
	}

	for (int i = 1; i <= n; i++) {
		if (groups[i] == 0) continue;
		gc[groups[i]] = gc[groups[i]] > cost[i] ? cost[i] : gc[groups[i]];
	}

	int lowCost = 0;
	for (int i = 1; i <= g; i++) {
		 lowCost += gc[i];
	}
	printf("%d\n", lowCost);
	return 0;
}