#pragma once
#include<cstdio>
#include<cstring>

int p[3001];

int llen;
struct Line {
	typedef long long point[2];

	point p[2];

	long long xmax, ymax, xmin, ymin;
	void init() {
		if (p[0][0] > p[1][0]) {
			xmax = p[0][0];
			xmin = p[1][0];
		}
		else {
			xmax = p[1][0];
			xmin = p[0][0];
		}
		if (p[0][1] > p[1][1]) {
			ymax = p[0][1];
			ymin = p[1][1];
		}

		else {
			ymax = p[1][1];
			ymin = p[0][1];
		}
	}
}lines[3000];

long long ccw(Line l1, long long p[2]) {
	return l1.p[0][0] * l1.p[1][1] + l1.p[1][0] * p[1] + p[0] * l1.p[0][1] - l1.p[0][0] * p[1] - l1.p[1][0] * l1.p[0][1] - p[0] * l1.p[1][1];
}

bool isCross(Line l1, Line l2) {
	if (ccw(l1, l2.p[0]) * ccw(l1, l2.p[1]) > 0 || ccw(l2, l1.p[0]) * ccw(l2, l1.p[1]) > 0) return false;

	bool ret = false;

	ret |= l1.xmin > l2.xmax;
	ret |= l1.xmax < l2.xmin;
	ret |= l1.ymax < l2.ymin;
	ret |= l1.ymin > l2.ymax;

	return !ret;
}

int find(int i) {
	if (p[i] < 0) return i;
	return p[i] = find(p[i]);
}

void join(int i1, int i2) {
	int pa[2] = { find(i1), find(i2) };

	if (pa[0] == pa[1]) return;

	if (p[pa[0]] > p[pa[1]]) {
		int temp = pa[0];
		pa[0] = pa[1];
		pa[1] = temp;
	}

	p[pa[0]] += p[pa[1]];
	p[pa[1]] = pa[0];
}

int BOJ2162() {
	int n;
	scanf("%d\n", &n);
	memset(p, -1, sizeof(p));

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld %lld\n", &lines[i].p[0][0], &lines[i].p[0][1], &lines[i].p[1][0], &lines[i].p[1][1]);
		lines[i].init();

		for (int j = 0; j < i; j++) {
			if(isCross(lines[j],lines[i])) join(i, j);
		}
	}

	int min = 0;
	int num = 0;
	for (int i = 0; i < n; i++) {
		if (p[i] < 0) {
			min = p[i] < min ? p[i] : min;
			num++;
		}
	}
	printf("%d\n%d\n", num, -min);

	return 0;
}