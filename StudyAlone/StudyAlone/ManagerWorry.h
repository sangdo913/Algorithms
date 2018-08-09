//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWR8UbE6-1ADFAUr

#include<cstdio>
#include<cstring>

struct info {
	int rate, team;
};
info rate[201];
info temp[201];

void mergeSort(int le, int m, int ri) {
	int l = le, k = le, r = m + 1;

	while (l <= m && r <= ri) {
		temp[k++] = rate[l].rate < rate[r].rate ? rate[l++] : rate[r++];
	}
	while (l <= m) temp[k++] = rate[l++];
	while (r <= ri) temp[k++] = rate[r++];

	int len[2] = { 0, 0};
	for (int i = le; i <= ri; i++) {
		
		rate[i] = temp[i];
	}
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, m, r);
	}
}

const int MOD = 1000000007;
long long pro[101][101];
int size[2];


void swap(int &i1, int &i2, int *ind) {
	int temp = ind[i1];
	ind[i1] = ind[i2];
	ind[i2] = temp;
}

int ManagerWorry() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);

		int t;

		for (int i = 0; i < n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 0;
		}
		for (int i = n; i < 2 * n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 1;
		}

		merge(0, 2 * n - 1);
		memset(pro, 0, sizeof(pro));

		size[0] = size[1] = 0;
		pro[0][0] = 1;

		for (int i = 0; i < 2 * n; i++) {
			int nt = rate[i].team;
			size[nt]++;

			for (int j = n - 1; j >= 0; j--) {
				for (int k = 0; k < n; k++) {
					if (pro[j][k]) {
						int remains = size[nt ^ 1] - j;

						if (remains) {
							pro[j + 1][k + (nt ^ 1)] = ((pro[j + 1][k + (nt ^ 1)] + pro[j][k] * remains)) % MOD;
						}
					}
				}
			}
		}

		printf("#%d ", tc);
		for (int i = 0; i <= n; i++) {
			printf("%lld ", pro[n][i]);
		}
		printf("\n");

	}
	return 0;
}