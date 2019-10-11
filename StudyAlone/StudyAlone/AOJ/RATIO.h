#include<stdio.h>

long long n, m, z;

bool decision(int cnt) {
	return (m + cnt) * 100 / (n + cnt)> z;
}

int main() {
	int tc;
	scanf("%d", &tc);

	while (tc--) {
		scanf("%ld %ld", &n, &m);
		z = (m * 100) / n;

		long long s = 0, e = 2000000000;
		int cnt = 100;
		int mid;
		while (s<=e) {
			mid = (s + e) / 2;
			if (decision(mid)) {
				e = mid-1;
			}
			else s = mid+1;
		}
		printf("%d\n", (m+s)*100/(n+s) == z ?-1 : s);
	}
	return 0;
}