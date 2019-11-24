#include<stdio.h>

int val[100000][2];
int n;
int check[100000];

bool mcmp0(int i, int j) {
	int diff1 = val[i][0] - val[j][1];
	int diff2 = val[j][0] - val[i][1];
	return diff1 > diff2;
}

bool mcmp1(int i, int j) {
	int diff1 = val[i][1] - val[j][0];
	int diff2 = val[j][1] - val[i][0];
	return diff1 > diff2;
}
int arr0[100000];
int arr1[100000];
int temp[100000];

void mergeSort(int *arr, int s, int e, bool(*cmp)(int, int)) {
	int l = s, m = (s + e) / 2, r = m + 1, k = l;

	while (l <= m && r <= e) temp[k++] = cmp(arr[l], arr[r]) ? arr[l++] : arr[r++];
	while (l <= m) temp[k++] = arr[l++];
	while (r <= e) temp[k++] = arr[r++];
	for (int i = s; i <= e; ++i) arr[i] = temp[i];
}

void merge(int *arr, int l, int r, bool(*cmp)(int, int)) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(arr,l, m, cmp);
		merge(arr,m+1, r, cmp);
		mergeSort(arr, l, r, cmp);
	}
}

int main() {
	int tc;
	scanf("%d", &tc);
	for(int t = 1; t <= tc; t++) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &val[i][0], &val[i][1]);
			arr1[i] = arr0[i] = i;
		}
		merge(arr0, 0, n - 1, mcmp0);
		merge(arr1, 0, n - 1, mcmp1);
		int c0 = 0, c1 = 0;
		long long res = 0;
		for (int i = 0; i < n; ++i) {
			if (i & 1) {
				while (check[arr1[c1]] == t) c1++;
				res -= val[arr1[c1]][1];
				check[arr1[c1]] = t;
			}
			else {
				while (check[arr0[c0]] == t) c0++;
				res += val[arr0[c0]][0];
				check[arr0[c0]] = t;
			}
		}
		
		printf("#%d %lld\n", t, res);
	}

	return 0;
}
