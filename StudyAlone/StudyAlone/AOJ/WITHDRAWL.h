#include<stdio.h>
#include<algorithm>
#define MIN(x,y) ((x) < (y) ? (x) : (y))

using namespace std;

int R[1000], C[1000];
double temp[1000];
int idx[1000];
int n, k;

bool cmp(int a, int b) {
	return temp[a]> temp[b];
}

bool decision(double in) {
	for (int i = 0; i < n; ++i) temp[i] = in * C[i] - R[i], idx[i] = i;
	sort(idx, idx + n, cmp);
	double v = 0;
	for (int i = 0; i < k; ++i) v += temp[idx[i]];
	return v >= 0;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		double res = 2;

		scanf("%d %d", &n, &k);
		int r, c;

		for (int i = 0; i < n; ++i) {
			scanf("%d %d", R+i, C+i);
		}

		int cnt = 100;
		double s = 0, e = 1;
		while (cnt--) {
			res = (s + e) / 2;
			if (decision(res)) {
				e = res;
			}
			else s = res;
		}

		printf("%0.10lf\n", res);
	}

	return 0;
}