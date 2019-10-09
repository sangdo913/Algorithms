#include<stdio.h>
#include<algorithm>
#include<queue>

using namespace std;

double nums[6][6];
double res[6][6];
int n;

double f(int d, double x) {
	double ret = 0;
	for (int i = 0; i < d; ++i) {
		double temp = 1;
		for (int j = 0; j < d - i; ++j) {
			temp *= x;
		}
		ret += temp * nums[d][i];
	}
	ret += nums[d][d];
	return ret;
}

bool decision(int d, double a) {
	return f(d,a)*f(d-1,a) < 0;
}

double bs(int d,double s, double e) {
	double m;
	int cnt = 100;
	while (cnt--) {
		m = (s + e) / 2;
		if (decision(d,m)) {
			s = m;
		}
		else e = m;
	}
	return m;
}
int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &n);
		for (int i = 0; i < n+1; ++i) {
			scanf("%lf", &nums[n][i]);
		}

		for (int i = n - 1; i>=0; --i) {
			for (int j = 0; j < i+1; ++j) {
				nums[i][j] = nums[i + 1][j] * (i+1 - j);
			}
		}

		for (int i = 1; i <= n; ++i) {
			res[i-1][0] = -10;
			res[i-1][i] = 10;
			for (int j = 1; j <= i; ++j) {
				res[i][j] = bs(i, res[i - 1][j-1], res[i - 1][j]);
			}
		}

		for (int i = 1; i <=n ; ++i) printf("%.10lf ", res[n][i]);
		printf("\n");
	}
	return 0;
}