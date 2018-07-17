#pragma once
#include<cstdio>
#include<cstring>
#define MOD 1000000007
long long celcius[49][3];
long long pizza[51][100001] = { 0 };
long long p[51];
char nums[10];

bool check(int n, int nn, int k) {
	memset(nums, '0', sizeof(char) * nn);
	int r = 0;
	bool ch2[10] = { false };
	int i = nn -1 ;
	int save = n;
	while (n) {
		nums[i] = n % 10;

		if (nums[i] >= k) return false;
		nums[i] += '0';
		n /= 10;
		i--;
	}
	bool ch = true;
	for (int i = 0; i < nn; i++) {
		ch2[nums[i] - '0'] = true;
	}

	for (int i = 0; i < k; i++) {
		if (ch2[i] == false) return false;
	}

	for (int i = 0; i < nn; i++) {
		if ((nums[i] == nums[(i + nn-1) % nn]) || (nums[i] == nums[(i + 1) % nn])) {
			ch = false;
			break;
		}
	}
	nums[nn] = 0;

	if (ch) {
		//printf("%s\n", nums);
	}
	return ch;
}

int pow(int num, int i) {
	if (i == 1) {
		return num;
	}
	int half = pow(num, i / 2);
	half *= half;

	return i & 1 ? half * num : half;
}

int print(int n, int k) {
	long long max = pow(10, n);
	int r = 0;
	for (long long i = 0; i < max; i++) {
		r += check(i, n,k);
	}
	return r;
}

void init()
{
	for (int i = 1; i < 51; i++) {
		p[i] = 1;
		
		for (int j = 2; j <= i; j++) {
			p[i] *= j;
			p[i] %= MOD;
		}
	}

	for (int n = 2; n <= 100000; n++) {
		pizza[2][n] = n & 1 ? 0 : 2;
	}

	for (int k = 3; k <= 50; k++) {
		pizza[k][k] = p[k];

	
		for (int n = k + 1; n <= 100000; n++) {
			pizza[k][n] = (k - 2) * pizza[k][n-1];
			pizza[k][n] %= MOD;
			pizza[k][n] += k * pizza[k-1][n - 1];
			pizza[k][n] %= MOD;
			pizza[k][n] += k * pizza[k-1][n - 2];
			pizza[k][n] %= MOD;
			pizza[k][n] += (k-1) * pizza[k][n-2];
			pizza[k][n] %= MOD;
		}
	}
}

int PIZZA() {
	init();
	/*
	int t;
	scanf("%d\n", &t); 

	celcius[1][1] = celcius[1][0] = celcius[0][0] = 1;
	
	for (int i = 2; i < 49; i++) {
		celcius[i][0] = 1;
	
		for (int j = 1; j < 3; j++) {
			celcius[i][j] = celcius[i - 1][j-1] + celcius[i-1][j];
			celcius[i][j] %= MOD;
		}
			

		celcius[i][i] = 1;
	}

	
	
	
	for (int tc = 1; tc <= t; tc++) {
		int n, k;
		scanf("%d %d\n", &n, &k);

		long long res = k == 1 ? 0 : 1;

		while (n - k > 1 && k > 2) {
			res *= celcius[k - 2][2];
			res %= MOD;
			n -= 2;
		}

		if (n == k) {
			for (int i = 2; i <= k; i++) {
				res *= i;
				res %= MOD;
			}
				
		}

		else if (k == 2) {
			res = n & 1 ? 0 : res * 2;
			res %= MOD;
		}

		else {
			for (int i = 2; i <= k; i++) {
				res *= i;
				res %= MOD;
			}
			int some = 1;
			some *= (k - 2)*(k-1) - (k > 3);
			res *= some;
			res %= MOD;
		}
*/
		//printf("#%d %lld\n", tc, res);
		int k = 4, n = 8;
		int res = (k - 2)*print(n - 1, k) + k * (print(n - 1, k - 1) + print(n - 2, k - 1) ) + (k - 1)* print(n - 2, k);
		printf("s[n,k] %d, cal[n,k] : %d\n", print(n, k), res);

		//printf("%d %d %d\n", print(n - 1, k), print(n-1,k-1), print(n-2,k-1));
		
		//print(5, 4);
		//printf("%d\n", r);
		printf("%d\n", pizza[k][n]);
	//}
	return 0;
}