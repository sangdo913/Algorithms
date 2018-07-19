#pragma once
#include<cstdio>
#include<cstring>
using namespace std;

int items[2000], temp[2000];
bool used[2000];
int st[2000][2];
int t1, t2;

int n, sum;

void mergeSort(int left, int m, int right) {
	int l = left, k = left, r = m + 1;
	while (l <= m && r <= right) {
		if (items[l] < items[r]) {
			temp[k++] = items[r++];
		}
		else {
			temp[k++] = items[l++];
		}
	}

	while (l <= m) temp[k++] = items[l++];
	while (r <= right) temp[k++] = items[r++];
	for (int i = left; i <= right; i++) {
		items[i] = temp[i];
	}
}

void merge(int l, int r) {
	if (l < r)
	{
		int m = (l + r) / 2;
		merge(l,m);
		merge(m + 1, r);
		mergeSort(l, m, r);
	}
}


bool find(int depth) {
	if (depth == 1) {
		int all = 0;
		for (int i = 0; i < n && all != sum; i++) {
			if (used[i]) continue;

			if (all + items[i] <= sum) {
				all += items[i];
				st[t2++][1] = i;
				used[i] = true;
			}
		}

		while (t2 != 0 && all != sum) {
			int save = st[--t2][1];
			int idx = save + 1;
			used[save] = false;
			all -= items[save];

			while (idx < n && items[save] == items[idx]) idx++;

			for (; idx < n; idx++) {
				if (used[idx]) continue;

				if (all + items[idx] <= sum) {
					all += items[idx];
					st[t2++][1] = idx;
					used[idx] = true;
				}
				if (all == sum) break;
			}
		}

		return all == sum;
	}


	st[t1++][0] = -1;
	int all = 0;
	while (true) {
		int save = st[--t1][0];
		int idx = save+1;
		
		if (save == -1) {
			all = 0;
		}
		else {
			used[save] = false;
			all  -= items[save];
		}

		while (save != -1 && items[save] == items[idx]) idx++;

		while (idx < n && all != sum) {
			if (all + items[idx] <= sum) {
				all += items[idx];
				st[t1++][0] = idx;
				used[idx] = true;
			}
			idx++;
		}

		if(all == sum && find(1)) return true;
	}

	return false;
}

int JinymetInDesert() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d\n", &n);

		memset(used, false, sizeof(used));
		sum = 0;
		t1 = t2 = 0;

		for (int i = 0; i < n; i++) {
			scanf("%d \n", &items[i]);
			sum += items[i];
		}
		sum /= 3;
		merge(0, n - 1);
		find(0);

		printf("#%d\n", tc);

		while (t1) {
			printf("%d ", items[st[--t1][0]]);
		}
		printf("\n");
		while (t2) {
			printf("%d ", items[st[--t2][1]]);
		}
		printf("\n");

		for (int i = 0; i < n; i++) {
			if (used[i] == false) printf("%d ", items[i]);
		}
		printf("\n");

	}
	return 0;
}