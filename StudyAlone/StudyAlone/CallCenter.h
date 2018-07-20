#pragma once
#include<cstdio>
#include<cstring>
using namespace std;

int info[100001][2];
int n, k, l;
enum TYPE {TIME, MI};

int nums[4];

int max(int i1, int i2) {
	return i1 < i2 ? i2 : i1;
}

int CallCenter() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d\n", &n, &k, &l);

		int res = 0;
		nums[1] = nums[2] = nums[3] = 0;

		for (int i = 1; i <= n; i++) {
			scanf("%d %d\n", &info[i][TIME], &info[i][MI]);
		}

		int good = 0;
		int time = 0;
		for (int idx = 1; idx <= n; idx++) {
			good += 10;
			time += info[idx][TIME];

			int extime = time - l;
			int notgood = 0;
			int mi = info[idx][MI];
			nums[mi] += info[idx][TIME] - k;

			for (int i = 1; i < 4; i++) {
					if (extime <= 0) break;
					if (extime < nums[i]) {
						notgood += extime * i;
						extime = 0;
						break;
					}
					else {
						notgood += i * (nums[i]);
						extime -= nums[i];
					}
				
			}

			if (extime <= -k) continue;
			if (extime > 0) break;
			res = max(good - notgood, res);
		}

		printf("#%d %d\n", tc, res);
	}

	return 0;
}