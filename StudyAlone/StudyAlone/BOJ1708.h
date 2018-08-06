//https://www.acmicpc.net/problem/1708
//ºí·Ï ²®Áú
#pragma once
#include<cstdio>

long long p[100000][2];
int temp[100000], idxes[100001];
int sta[100000], top;

long long ccw(long long p1[2], long long p2[2], long long p3[2]) {
	return p1[0] * p2[1] + p2[0] * p3[1] + p3[0] * p1[1] - p1[0] * p3[1] - p2[0] * p1[1] - p3[0] * p2[1];
}

long long dist(long long p1[2], long long p2[2]) {
	long long r[2] = { p1[0] - p2[0], p1[1] - p2[1] };
	return r[0] * r[0] + r[1] * r[1];
}

void merge(int left, int right) {
	if (left < right) {
		int m = (left + right) / 2;
		merge(left, m);
		merge(m + 1, right);

		int l = left, r = m + 1, k = left;
		while (l <= m && r <= right) {
			long long tcc = ccw(p[idxes[0]], p[idxes[l]], p[idxes[r]]);
			if (tcc == 0) {
				temp[k++] = dist(p[idxes[0]], p[idxes[l]]) > dist(p[idxes[0]], p[idxes[r]]) ? idxes[r++] : idxes[l++];
			}
			else temp[k++] = tcc > 0 ? idxes[l++] : idxes[r++];
		}
		
		while (l <= m) temp[k++] = idxes[l++];
		while (r <= right) temp[k++] = idxes[r++];

		for (int i = left; i <= right; i++) idxes[i] = temp[i];
	}
}

int BOJ1708() {
	int n;
	scanf("%d\n", &n);
	
	long long min[2];

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld\n", &p[i][0], &p[i][1]);
		 
	}

	for (int i = 0; i < n; i++) idxes[i] = i;
	min[0] = p[0][0];
	min[1] = p[0][1];
	int imin = 0;

	for (int i = 1; i < n; i++) {
		if (min[1] == p[i][1]) {
			if (min[0] < p[i][0]) {
				min[0] = p[i][0];
				imin = i;
			}
		}
		else if (min[1] > p[i][1]) {
			min[1] = p[i][1];
			min[0] = p[i][0];
			imin = i;
		}
	}

	int temp = imin;
	idxes[imin] = 0;
	idxes[0] = imin;

	merge(1, n - 1);

	int i = 2;

	int prev = idxes[1], pprev = idxes[0], now = idxes[i];

	while (i < n && ccw(p[pprev], p[prev], p[now]) == 0) {
		prev = now;
		now = idxes[++i];
	}

	for (; i < n; i++) {
		now = idxes[i];

		while (top > 0 && ccw(p[pprev], p[prev], p[now]) <= 0) {		
			prev = pprev;
			pprev = sta[--top];
		}
		
		sta[top++] = pprev;
		pprev = prev;
		prev = now;
	}

	printf("%d\n", top + 2);
	return 0;
}