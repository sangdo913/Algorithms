#include<cstdio>
#include<stdlib.h>
#include"user2.cpp"
#include<ctime>
// minimum score

int origin[256];
int in[200];

int check(int arr[200]) {
	int num = 0, correct = 0;

	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			num += arr[i] == origin[j];
		}
	}

	for (int i = 0; i < 200; ++i) correct += origin[i] == arr[i];
	return (correct << 8) + num;
}

void init() {
	for (int i = 0; i < 200; ++i) in[i] = 0;
	for (int i = 0; i < 256; ++i) {
		int idx;
		idx = rand() % 256;
		int temp = origin[i];
		origin[i] = origin[idx];
		origin[idx] = temp;
	}
}

extern void func(int in[200]);

int main() {
	clock_t st, ed;
	srand(time(0));
	st = clock();
	int cnt = 1;
	for (int i = 0; i < 256; ++i) origin[i] = cnt++;

	int T = 50;
	int totalScore = 0;
	for (int tc = 1; tc <= T; tc++) {
		init();
		func(in);
		int res = check(in);
		if ((res >> 8) != 200) totalScore += 1000000;
	}
	ed = clock();
	printf("Score : %d\n", (ed - st) + totalScore); 

	return 0;
}