#include<cstdio>

int main() {
	long long n, k;
	scanf("%lld %lld\n", &n, &k);

	if (k - 1 <= n) printf("%lld\n", (k - 1) / 2);
	else if(n < (k / 2 + 1)){
		printf("0\n");
	}
	else {
		printf("%lld\n", n - k / 2);
	}
	return 0;
}