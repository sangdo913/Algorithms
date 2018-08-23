//https://www.acmicpc.net/submit/2102/9861136
// 보석 줍기
#pragma once
#include<cstdio>

long long arr[100001];
long long nums[100001];
long long temp;
long long n, m;

int BOJ2102() {
	scanf("%lld %lld\n", &n, &m);
	long long max = 0;
	long long res = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld\n", &nums[i]);
		arr[i] = arr[i - 1] + nums[i];
	}
	
	int  cnt = m;

	for (int i = m; i <= n; i++) {
		long long temp = (arr[i] - arr[i - m]) * 1000 / m;
		long long nm = (max + nums[i])* 1000 / (cnt+1);
		if (temp > nm) {
			max = arr[i] - arr[i - m];
			cnt = m;
			res = res < temp ? temp : res;
		}
		else {
			cnt++;
			max += nums[i];
			res = res < nm ? nm : res;
		}
	}
	printf("%lld\n", res);
	return 0;
}