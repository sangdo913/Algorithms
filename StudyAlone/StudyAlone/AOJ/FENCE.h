#include<stdio.h>
int N;
int arr[20000];

int st[2][20000], stsize;

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &N);
		stsize = 0;
		int res = 0;
		for (int i = 0; i < N; ++i) {
			scanf("%d", arr + i);
			
		}

		for (int i = 0; i < N; ++i) {
			int idx = i;
			while (stsize && st[0][stsize - 1] > arr[i]) {
				--stsize;
				res = MAX(res, st[0][stsize] * (i - st[1][stsize]));
				idx = st[1][stsize];
			}
			st[0][stsize] = arr[i];
			st[1][stsize++] = idx;
		}

		while (stsize) {
			--stsize;
			res = MAX(res, st[0][stsize] * (N - st[1][stsize]));
		}
		printf("%d\n", res);
	}

	return 0;
}