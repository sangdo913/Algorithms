//https://www.acmicpc.net/problem/1019
#pragma once
#include<cstdio>

long long pow(int cnt) {
	if (cnt < 0) return 0;

	if (cnt == 0) {
		return 1;
	}

	long long half = pow(cnt / 2);
	half *= half;
	if (cnt & 1) half *= 10;
	return half;
}

long long cnt[10];

int getDigit(long long n) {
	int res = 0;
	while (n) {
		res++;
		n /= 10;
	}
	return res-1;
}
int BOJ1019() {
	long  long n;
	scanf("%lld\n", &n);

	int digit = getDigit(n);
	long long p = pow(digit);

	for (int i = 0; i < digit; i++) {
		cnt[0] -= (digit - i)*(pow(i+1)-pow(i));
	}

	cnt[0] -= digit;

	for (int i = digit; i > 0; i--) {
		int fr = n / p;

		for (int i = 0; i < fr; i++) {
			cnt[i] += p;
		}
		
		for (int i = 0; i < 10; i++) cnt[i] += fr*digit*pow(digit-1);

		n %= p;

		cnt[fr] += n + 1;
		digit--;
		p /= 10;
	}

	for (int i = 1; i <= n; i++) {
		cnt[i]++;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", cnt[i]);
	}
	return 0;
}