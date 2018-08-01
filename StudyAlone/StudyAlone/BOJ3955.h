#pragma once
#include<cstdio>

int BOJ3955() {
	long long pa[2], pb[2], q, r;

	long long t, a, b;
	scanf("%lld\n", &t);

	while (t--) {
		long long a, b;

		bool changed = false;
		scanf("%lld %lld\n", &a, &b);

		if (b == 1 && a < 1000000000) {
			printf("%lld\n", a + 1);
			continue;
		}
		else if (b == 1) {
			printf("%s\n", "IMPOSSIBLE");
			continue;
		}

		long long t[2] = { a,b };

		pa[1] = 1;
		pa[0] = 0;
		pb[1] = 0;
		pb[0] = 1;

		if (a < b) {
			long long temp = a;
			a = b;
			b = temp;
			changed = true;
		}


		while (b) {
			q = a / b;
			r = a % b;
			long long s = pa[1] - q * pa[0];
			long long t = pb[1] - q * pb[0];
			pa[1] = pa[0];
			pb[1] = pb[0];
			pa[0] = s;
			pb[0] = t;
			a = b;
			b = r;
		}

		if (changed) {
			long long temp = pa[1];
			pa[1] = pb[1];
			pb[1] = temp;
		}

		if (pa[1] >= 0 || pb[1] <= 0) {
			long long q = pb[1] / t[0] + 1;
			pa[1] -= q*t[1];
			pb[1] += q*t[0];
		}

		if (pb[1] > 1000000000 || pa[1] >= 0) {
			long long q = (pb[1] - 1000000000) / t[0] + 1;
			
			pa[1] += q*t[1];
			pb[1] -= q*t[0];
		}

		if (a == 1 && pa[1] < 0 && pb[1] > 0) printf("%lld\n", pb[1]);
		else printf("%s\n", "IMPOSSIBLE");
	}

	return 0;
}