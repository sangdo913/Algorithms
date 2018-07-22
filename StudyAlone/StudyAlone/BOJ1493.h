#pragma once
#include<cstdio>
#include<cstring>
int info[3];
long long boxes[20] = { 0 }, need[20] = { 0 };

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

int getLog(int i1) {
	int res = -1;
	while (i1) {
		res++;
		i1 >>= 1;
	}
	return res;
}

int getLen() {
	int res = 0;

	for (int i = 19; i > 0; i--) {
		if (need[i] > boxes[i]) {
			need[i] -= boxes[i];
			res += boxes[i];
		}
		else {
			res += need[i];
			need[i] = 0;
		}

		if (need[i] > 1000000) return -1;
		need[i - 1] += need[i] * 8;
	}
	
	return need[0] > boxes[0] ? -1 : res + need[0];
}

void FillBox(long long l, long long w, long long h) {
	if (l == 0 || w == 0 || h == 0) return ;

	int len = min(getLog(l), getLog(w));
	len = min(len, getLog(h));

	int mi = 1 << len;

	long long  r[3] = { (l>>(len)) , w >>(len), h>>(len) };
	need[len] += r[0] * r[1] * r[2];
	for (int i = 1; i < 0b1000; i++) {
		int t[3];
		t[0] = i & 0b100 ? l - (r[0]<<len) : (r[0]<<len);
		t[1] = i & 0b10 ? w - (r[1]<<len) : (r[1]<<len);
		t[2] = i & 0b1 ? h - (r[2]<<len) : (r[2]<<len);

		FillBox(t[0], t[1], t[2]);
	}
}

int BOJ1493() {

	scanf("%d %d %d\n", info, info+1, info+2);
	int n;
	scanf("%d\n", &n);
	while (n--) {
		int in[2];
		scanf("%d %d\n", in, in + 1);
		boxes[in[0]] = in[1];
	}
	FillBox(info[0], info[1], info[2]);
	printf("%d\n",getLen());
	return 0;
}