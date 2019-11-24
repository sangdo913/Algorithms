#include<stdio.h>
#define SIZE 5000001
int que[SIZE];
int fr, re;
int main() {
	int tc;
	scanf("%d", &tc);
	
	while (tc--) {
		fr = re = 0;
		int n, k;
		scanf("%d %d", &k, &n);

		long long seed = 1983;
		int v = 1983;
		
		long long sum = 0;
		long long res = 0;
		while (n--) {
			sum += v;
			que[re++%SIZE] = v;
			while (re != fr && sum > k) {
				sum -= que[fr++%SIZE];
			}
			res += sum == k;
			seed = (seed * 214013LL + 2531011LL) % ((1LL << 32));
			v = (seed)%10000+1;
		}
		printf("%d\n", res);
	}
	return 0;
}