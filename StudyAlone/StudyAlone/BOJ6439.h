//https://www.acmicpc.net/problem/6439
//±³Â÷
#pragma once
#include<cstdio>

struct LINE {
	typedef long long point[2];

	point p[2];
	long long max[2], min[2];
	void init() {
		if (p[0][0] < p[1][0]) {
			max[0] = p[1][0];
			min[0] = p[0][0];
		}
		else {
			max[0] = p[0][0];
			min[0] = p[1][0];
		}

		if (p[0][1] < p[1][1]) {
			max[1] = p[1][1];
			min[1] = p[0][1];
		}
		else {
			max[1] = p[0][1];
			min[1] = p[1][1];
		}
	}
};

long long ccw(LINE l1, long long p[2]) {
	return l1.p[0][0] * l1.p[1][1] + l1.p[1][0] * p[1] + p[0]*l1.p[0][1]- l1.p[0][0] * p[1] - l1.p[1][0] * l1.p[0][1] - p[0] * l1.p[1][1];
}

bool isCross(LINE l1, LINE l2) {
	if (ccw(l1, l2.p[0]) * ccw(l1, l2.p[1]) > 0) return false;
	if (ccw(l2, l1.p[0]) * ccw(l2, l1.p[1]) > 0) return false;

	if (l1.min[0] > l2.max[0]) return false ;
	if (l1.max[0] < l2.min[0]) return false;
	if (l1.min[1] > l2.max[1]) return false;
	if (l1.max[1] < l2.min[1]) return false;

	return true;
}

int BOJ6439() {
	int t;
	scanf("%d\n", &t);
	while (t--) {
		LINE line;
		scanf("%lld %lld %lld %lld\n", &line.p[0][0], &line.p[0][1], &line.p[1][0], &line.p[1][1]);
		long long xl, yl, xh, yh;
		scanf("%lld %lld %lld %lld", &xl, &yh, &xh, &yl);
		if (xl > xh) {
			long long temp = xl;
			xl = xh;
			xh = temp;
		}

		if (yl > yh) {
			long long temp = yl;
			yl = yh;
			yh = temp;
		}

		LINE l[4];
		l[0].p[0][0] = xl;
		l[0].p[1][1] = l[0].p[0][1] = yh;
		l[0].p[1][0] = xh;
	
		l[1].p[1][0] = l[1].p[0][0] = xh;
		l[1].p[0][1] = yh;
		l[1].p[1][1] = yl;

		l[2].p[0][1] = l[2].p[1][1] = yl;
		l[2].p[0][0] = xh;
		l[2].p[1][0] = xl;

		l[3].p[0][0] = l[3].p[1][0] = xl;
		l[3].p[0][1] = yl;
		l[3].p[1][1] = yh;

		line.init();
		for (int i = 0; i < 4; i++) l[i].init();

		bool res = false;

		res |= line.p[0][0] >= xl && line.p[0][0] <= xh && line.p[0][1] >= yl && line.p[0][1] <= yh;
		res |= line.p[1][0] >= xl && line.p[1][0] <= xh && line.p[1][1] >= yl && line.p[1][1] <= yh;

		for (int i = 0; i < 4 && !res; i++) {
			res |= isCross(l[i], line);
		}

		printf("%c\n", res ? 'T' :'F');
	}
	return 0;
}