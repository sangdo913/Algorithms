#pragma once
#include<cstdio>
#include<cstring>
#define INF 987654321

enum TURN {H = 0, S = 1};
int cache[50][50][2], prices[50];
int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

int same(int i1) {
	return i1;
}

int mi(int i1) {
	return -i1;
}

int(*cal[2])(int, int) = { max, min };
int(*conv[2])(int i1) = { same, mi };
int rets[2] = { -INF, INF };

int diff(int turn, int l, int r) {
	if (l > r) {
		return 0;
	}

	int &ret = cache[l][r][turn];
	if (ret != -1) return ret;

	ret = rets[turn];

	ret = cal[turn](ret, diff(turn ^ 1, l + 1, r) + conv[turn](prices[l])); // ¿ÞÂÊ²¨ ÇÏ³ª ¶¼±â
	ret = cal[turn](ret, diff(turn ^ 1, l, r - 1) + conv[turn](prices[r])); //¿À¸¥ÂÊ²¨ ÇÏ³ª »©±â
	if (r != l) {
		ret = cal[turn](ret, diff(turn ^ 1, l + 2, r)); //¿ÞÂÊ²¨ µÎ°³ ¶¼±â;
		ret = cal[turn](ret, diff(turn ^ 1, l, r - 2)); // ¿À¸¥ÂÊ²¨ µÎ°³ »©±â
	}

	return ret;
}

int NUMBERGAME(){
	int t;
	scanf("%d\n", &t);

	while (t--) {
		memset(cache, -1, sizeof(cache));

		int n;
		scanf("%d\n", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d \n", &prices[i]);
		}

		int res = diff(H, 0, n - 1);
		printf("%d\n", res);
	}

	return 0;
}