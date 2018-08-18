#pragma once
#include<cstdio>
#include<cstring>
int check[3][100001];bool inque[100001];
int info[3][100001];
int idx[100001], temp[1000001];
int que[100000], f, r;


void merge(int left, int right) {
	if (left < right) {
		int m = (left + right) / 2;

		merge(left, m);
		merge(m + 1, right);

		int l = left, r = m + 1, k = l;

		while (l <= m && r <= right) {
			temp[k++] = info[0][idx[l]] < info[0][idx[r]] ? idx[l++] : idx[r++];
		}
		while (l <= m) temp[k++] = idx[l++];
		while (r <= right) temp[k++] = idx[r++];

		for (int i = left; i <= right; i++) {
			idx[i] = temp[i];
		}
	}
}

int CodeBattle081402() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);
		memset(check, 0, sizeof(check));
		memset(inque, false, sizeof(inque));
		for (int i = 1; i <= n; i++) idx[i] = i;

		for (int i = 0; i < 3; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d \n", &info[i][j]);
				check[i][info[i][j]]++;
			}
		}
		f = r = 0;

		merge(1, n);

		for(int ro = 0; ro < 3; ro++)
			for (int i = 1; i <= n; i++) {
				if (check[ro][i] == 0) {
					if (inque[i]) continue;
					inque[i] = true;
					que[r++] = i;
					check[0][i]--;
				}
			}

		while (f != r) {
			int now = que[f++];

			int conv = idx[now];
			check[1][info[1][conv]]--;
			if (check[1][info[1][conv]] == 0 && inque[info[1][conv]] == false) {
				inque[info[1][conv]] = true;
				que[r++] = info[1][conv];
				check[0][info[1][conv]]--;
			}

			check[2][info[2][conv]]--;
			if (check[2][info[2][conv]] == 0 && inque[info[2][conv]] == false) {
				inque[info[2][conv]] = true;
				que[r++] = info[2][conv];
				check[0][info[2][conv]]--;
			}
		}

		int res = 0;
		for (int i = 1; i <= n; i++) {
			res += inque[i];
		}
		printf("#%d %d\n", tc,res);
	}

	return 0;
}