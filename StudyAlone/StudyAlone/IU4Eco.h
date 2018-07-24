#pragma once
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.

long long pow(int n) {
	if (n == 0)return 1;
	long long half = pow(n / 2);

	half *= half;
	return n & 1 ? half * 3 : half;
}

int bs(long long value) {
	int l = 0, r = 22;

	while (l < r) {
		int m = (l + r) / 2;
		if (pow(m) + 2*m > value) {
			r = m;
		 }
		else {
			l = m + 1;
		}
	}
	return r - 1;
}

int maxv[20];

int move(long long diff, int pos, int sn, int star, long long value) {
	if (diff == value) return 1;
	if (sn < star) {
		return diff > value ? -1 : 0;
	}
	int ret = 0;
	
	for (int i = (star-1)*3; i >= pos; i--) {
		long long v = pow(sn - star) * (i - star + 1LL);
		long long temp = move(diff, i + 1, sn, star + 1, value + v);
		if (temp == -1) break;
		ret += temp;
	}
	return ret;
 }

void init(int st) {
	maxv[st] = 2 * 3* (st-1);
	for (int i = st-1; i > 0; i--) {
		maxv[i] = maxv[i + 1] + 2 * (3 * (i - 1)*pow(st - i));
	}
}

int Three[20];
int nums[20];
void three(int n) {
	int i = 0;
	while (n) {
		Three[i] = n % 3;
		n /= 3;
		i++;
	}
}

int solution(int n) {
	int answer = 0;
	int num = bs(n);
	init(num);
	int diff = n - (pow(num) + 2 * num);
	diff >>= 1;
	three(diff);
	for (int i = 0; i < num; i++) {
		nums[i] = (18 - i) * 3;
	}
	answer = move(diff, 0, num, 1, 0);

	return answer;
}