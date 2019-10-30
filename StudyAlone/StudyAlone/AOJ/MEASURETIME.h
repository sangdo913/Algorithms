#include<stdio.h>

int arr[1000001];
int main() {
	int tc;
	int n;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &n);
		long long res = 0;
		for (int i = 1; i <= 1000000; ++i) arr[i] = 0;

		for (int i = 0; i < n; ++i) {
			int in;
			scanf("%d", &in);
			in = 1000001 - in;
			int a = in--;

			while (in) {
				res += arr[in];
				in &= (in - 1);
			}
			while (a <= 1000000) {
				arr[a]++;
				a += a & -a;
			}
		}
		printf("%lld\n", res);
	}

	return 0;
}