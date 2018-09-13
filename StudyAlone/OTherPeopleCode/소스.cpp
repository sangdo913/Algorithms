#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int v[100001];
int fibo[100001];
int MOD = 1234567;

int solution(int n) {

	if (n <= 2) return 1;

	if (v[n] != -1) {
		return v[n];
	}

	return v[n] = ((solution(n - 1) % MOD) + (solution(n - 2) % MOD)) % MOD;
}

int main() {
	int n;

	//scanf("%d", &n);

	for (int i = 0; i <= 100000; i++) {
		v[i] = -1;
	}

	v[0] = 0;
	v[1] = 1;
	fibo[0] = 0;
	fibo[1] = 1;
	for (int i = 2; i <= 100000; i++) {
		fibo[i] = fibo[i - 1] + fibo[i - 2];
		fibo[i] %= MOD;
	}

	for (int i = 0; i <= 100000; i++) {
		if (fibo[i] != solution(i)) printf("%d error! v[n] : %d, fibo[n] : %d\n", i, solution(i) , fibo[i]);
	}

	return 0;
}