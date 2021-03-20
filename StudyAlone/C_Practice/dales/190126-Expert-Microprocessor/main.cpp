#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <ctime>

static int seed = 0126;
static int pseudo_rand(void) {
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

#define MAX_CODE_LENGTH 10000
static unsigned char input_code[MAX_CODE_LENGTH];

static unsigned char sum1toNcode[21] = { 160, 129, 0, 1, 160, 137, 224, 162, 128, 41, 160, 130, 35, 160, 131, 161, 128, 66, 208, 163, 128 };

extern int make_code(unsigned char* code);
extern int run_code(unsigned char* code, int size, int arg);

int main() {
	//freopen("sample_input.txt", "r", stdin);

	int SCORE = 0;
	int start = clock();
	int ans = 0;
	int res = run_code(sum1toNcode, 21, 10);
	scanf("%d", &ans);
	if (ans != res) SCORE += 10000;
	int sz = make_code(input_code);
	for (int test = 0; test < 6000; test++) {
		res = run_code(input_code, sz, pseudo_rand() % 10001);
		scanf("%d", &ans);
		if (ans != res) SCORE += 10000;
	}
	SCORE += ((clock() - start) / (CLOCKS_PER_SEC / 1000));

	if (SCORE <= 3000)
		printf("PASS\n");
	else
		printf("SCORE: %d\n", SCORE);

	return 0;
}



