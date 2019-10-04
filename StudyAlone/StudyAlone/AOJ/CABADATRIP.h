#include<stdio.h>

int l[5000], m[5000], g[5000];
int n, k;

bool decision(int pos) {
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (l[i] <= pos) {
			sum += m[i] / g[i] + 1;
			continue;
		}
		int start = l[i] - m[i];
		if (pos < start) continue;
		sum += (pos- start) / g[i] + 1;
	}
	return k > sum;
}

int bs(int ed) {
	int st = 0;
	int m;
	while (st <= ed) {
		m = (st + ed)/2;
		if (decision(m)) {
			st = m+1;
		}
		else {
			ed = m - 1;
		}
	}
	return st;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; ++i) scanf("%d %d %d", l + i, m + i, g + i);

		printf("%d\n",  bs(8030000));
	}

	return 0;
}