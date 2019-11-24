#include<stdio.h>

double n, p;
int k;

bool decision(double c,int m) {
	double remain = n;
	while (m--) {
		remain *= p;
		remain -= c;
		if (remain <= 0)return true;
	}
	return false;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%lf %ld %lf", &n, &k, &p);
		p = 1 + p/1200;
		
		int cnt = 100;
		double s = 0, e = 1e12;
		double m;
		while (cnt--) {
			m = (s + e) / 2;
			if (decision(m, k)) {
				e = m;
			}
			else s = m;
		}
		printf("%.10lf\n", m);
	}
	return 0;
}
