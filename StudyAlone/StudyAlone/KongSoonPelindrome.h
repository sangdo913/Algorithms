#pragma once
#include<cstdio>
#include<cstring>
#include<time.h>
#include<stdlib.h>


int n, k, memoi[2001][2001] = { 0 }; // start, end;
int memoi2[2001][2001];
int price['z' + 1];
char str[2001] = { 0 };

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

//재귀 DP 구성
int getMin(int st, int ed) {
	if (st >= ed) return 0;

	int &ret = memoi2[st][ed];
	if (ret != -1) return ret;

	//st와 ed를 하나씩 떼어보기
	ret = str[st] == str[ed] ? getMin(st + 1, ed - 1) : 987654321;
	
	//st를 뒤에 삽입 or 제거
	ret = min(ret, getMin(st + 1, ed) + price[str[st]]);

	//ed를 앞에 삽입 or 제거
	ret = min(ret, getMin(st, ed - 1) + price[str[ed]]);

	return ret;
}

int KongSoonPelindrome()
{
	int t;
	scanf("%d\n", &t);

	//t = 100000;
	//srand(time(NULL));

	for (int tc = 1; tc <= t; tc++) {
		memset(memoi2, -1, sizeof(memoi2));

		scanf("%d %d\n", &n, &k);
		scanf("%s\n", str);
		int i1, i2;

		for (int i = 0; i < k; i++) {
			scanf("%d %d\n", &i1, &i2);

			price[i + 'a'] = i1 < i2 ? i1 : i2;
		}

		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				memoi[i][j] = i == j ? 0 : 987654321;
			}
		}

		//////////////// 반복문으로DP 구성
		for (int k = 1; k < n; k++) {
			int i = 0, j = k;

			for (int l = 0; l < n - k; l++) {
				memoi[i][j] = min(memoi[i][j], memoi[i + 1][j] + price[str[i]]);
				memoi[i][j] = min(memoi[i][j], memoi[i][j - 1] + price[str[j]]);
				if (str[i] == str[j]) memoi[i][j] = min(memoi[i][j], memoi[i + 1][j - 1]);
				i++; j++;
			}
		}
		///////////////////////////

		int res = getMin(0, n - 1);
		
		printf("#%d %d %d\n", tc, memoi[0][n - 1], res);
	}

	return 0;
}
