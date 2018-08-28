#pragma once
#include<cstdio>

int n, m;
char map[117][117];

struct cod {
	int r, c;
};

cod findMID(int r, int c) {
	int nc = c;
	
	while (map[r][nc] == 'B') {
		nc++;
	}

	int nr = r;
	while (map[nr][c] == 'B') {
		nr++;
	}
	return { (nr + r) / 2, (c + nc) / 2 };
}

int CodeforceAIM5A() {
	scanf("%d %d\n", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%s\n", map[i]+1);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 'B') {
				cod res = findMID(i, j);
				printf("%d %d\n", res.r, res.c);
				return 0;
			}
		}
	}
	return 0;

}