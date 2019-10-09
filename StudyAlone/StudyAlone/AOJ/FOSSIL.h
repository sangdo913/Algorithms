#include<stdio.h>

#define SIZE 100
int f[2][SIZE];
double from[2][SIZE];
double to[2][SIZE];
double a[2][SIZE];
double b[2][SIZE];
double xx[2][SIZE];
double y[2][SIZE];
int sz[2];

double calc(int id, int i ,double x) {
	return (x*a[id][i] + b[id][i]);
}

double getdiff(double x) {
	double v[2][4];
	int idx[2][4];
	int vlen[2] = { 0,0 };
	for (int d = 0; d < 2; ++d) {
		for (int i = 0; i < sz[d]; ++i) {
			if (from[d][i] <= x && x <= to[d][i]) idx[d][vlen[d]++] = i;
		}
	}

	for (int d = 0; d < 2; ++d) {
		double maxx = -100; double mmin = 200;
		for (int i = 0; i < vlen[d]; ++i) {
			double ans = calc(d, idx[d][i], x);
			maxx = ans < maxx ? maxx : ans;
			mmin = ans > mmin ? mmin : ans;
		}
		v[d][0] = mmin;
		v[d][1] = maxx;
	}

	if (v[0][0] > v[1][1] || v[0][1] < v[1][0]) return -1e10;
	if (v[0][0] <= v[1][0] && v[1][1] <= v[0][1]) {
		return v[1][1] - v[1][0];
	}
	if (v[1][0] <= v[0][0] && v[0][1] <= v[1][1]) {
		return v[0][1] - v[0][0];
	}
	if (v[0][0] < v[1][0]) return v[0][1] - v[1][0];
	else return v[1][1] - v[0][0];
}

double getans(double s, double e) {
	int cnt = 100;
	while (cnt--) {
		double a = (s+e * 2) / 3.0, b = (s * 2 + e) / 3.0;
		if (getdiff(a) > getdiff(b)) {
			s = b;
		}
		else e = a;
	}
	return (s + e) / 2;
}

int main() {
	int tc;
	scanf("%d", &tc);

	while (tc--) {
		scanf("%d %d", sz, sz + 1);

		double minx[2] = { 200,200 };
		double maxx[2] = { -200,-200 };
		for (int i = 0; i < sz[0]; ++i) scanf("%lf %lf", xx[0] + i, y[0] + i);
		for (int i = 0; i < sz[1]; ++i) scanf("%lf %lf", xx[1] + i, y[1] + i);
		for (int d = 0; d < 2; ++d) {

			for (int i = 0; i < sz[d]; ++i) {
				minx[d] = minx[d] < xx[d][i] ? minx[d] : xx[d][i];
				maxx[d] = maxx[d] > xx[d][i] ? maxx[d] : xx[d][i];
				f[d][i] = i;
				if (xx[d][i] != xx[d][(i + 1) % sz[d]]) {
					a[d][i] = (y[d][i] - y[d][(i + 1) % sz[d]]) / (xx[d][i] - xx[d][(i + 1) % sz[d]]);
					b[d][i] = y[d][i] - a[d][i] * xx[d][i];
				}
				else {
					a[d][i] = 0;
					b[d][i] = y[d][(i + 1) % sz[d]];
				}

				from[d][i] = xx[d][i];
				to[d][i] = xx[d][(i + 1) % sz[d]];

				if (from[d][i] > to[d][i]) {
					double t = from[d][i];
					from[d][i] = to[d][i];
					to[d][i] = t;
				}
			}
		}

		double res = getdiff(getans(minx[0] < minx[1] ? minx[1] : minx[0], maxx[0] > maxx[1] ? maxx[1] : maxx[0]));
		printf("%.10lf\n", res == -1e10 ? 0 : res);
	}
}
