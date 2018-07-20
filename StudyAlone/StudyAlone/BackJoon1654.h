//https://www.acmicpc.net/problem/1654
#pragma once
#include<cstdio>

long long lines[10000], temp[10000], k, n;

//���̸� len���� �� �� ������ ������ ���Ǻ��� ���� ��� true ��ȯ!
bool check(long long len) {
	long long num = 0;
	for (int i = 0; i < k; i++) {
		num += lines[i] / len;
	}
	return num < n;
}

long long bs(long long left, long long right) {
	while (left < right) {
		long long m = (left + right) / 2;

		//������ ���Ǻ��� ���ٸ� ���̸� �ٿ����Ѵ�!
		if (check(m)) {
			right = m;
		}
		//������ ���Ǻ��� ũ�ٸ� ���̸� �ø���!
		//���Ƶ� �ø���! -> upper_bound
		else {
			left = m + 1;
		}
	}
	return right - 1;
}

int LanCut() {
	scanf("%d %d\n", &k, &n);

	long long r = 0;
	for (int i = 0; i < k; i++) {
		scanf("%lld \n", &lines[i]);

		r = r < lines[i] ? lines[i] : r;
	}

	printf("%lld\n", bs(1,r+1));
	return 0;
}