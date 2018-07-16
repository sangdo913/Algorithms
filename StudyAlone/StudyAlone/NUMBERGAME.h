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

	//cal[] : 서하의 경우엔 - 점수가 큰 점수, 따라서 min을 이용해 계산
	//		  현우의 경우엔 + 점수가 큰 점수, 따라서 max를 이용해 계산
	//conv[] : 서하의 경우엔 점수를 얻으면 - 실행
	//		   현우의 경우엔 점수를 얻으면 + 실행
	ret = cal[turn](ret, diff(turn ^ 1, l + 1, r) + conv[turn](prices[l])); // 왼쪽꺼 하나 떼기
	ret = cal[turn](ret, diff(turn ^ 1, l, r - 1) + conv[turn](prices[r])); //오른쪽꺼 하나 빼기
	if (r != l) {
		ret = cal[turn](ret, diff(turn ^ 1, l + 2, r)); //왼쪽꺼 두개 떼기;
		ret = cal[turn](ret, diff(turn ^ 1, l, r - 2)); // 오른쪽꺼 두개 빼기
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