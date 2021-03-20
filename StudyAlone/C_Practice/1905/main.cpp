#include <stdio.h>
#include <time.h>
int check(unsigned char* key);
unsigned char KEY[200];
unsigned char res[200];
#include"user.cpp"

extern void test(unsigned char* key);

static int seed = 3;


int call_cnt = 0;

static int pseudo_rand()
{
	seed = seed * 214011 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

int check(unsigned char* key)
{
	++call_cnt;

	register int pos = 0, equal = 0;

	for (register int i = 0; i < 200; ++i)
	{
		if (key[i] == KEY[i]) ++pos;
	}

	for (register int i = 0; i < 200; ++i)
		for (register int j = 0; j < 200; ++j)
			if (key[i] == KEY[j]) ++equal;

	return 512 * pos + equal;
}

int main()
{
	int RESULT = 0;
	clock_t st = clock();

	for (int tc = 0; tc < 222; ++tc)
	{
		unsigned char pool[255]{};

		for (int c = 0; c < 200;++c)
		{
			int i = pseudo_rand() % 255;
			while (pool[i] == 1) i = pseudo_rand() % 255;

			KEY[c] = i + 1;
			pool[i] = 1;
		}

		test(res);

		for (int c = 0; c < 200; ++c)
			if (res[c] != KEY[c])
				RESULT += 10000;
	}

	printf("RESULT : %d\n", RESULT + (clock() - st) / (CLOCKS_PER_SEC / 1000));
	printf("TOTAL CALL COUNT : %d\n", call_cnt);
	printf("AVERAGE CALL COUNT : %d\n", call_cnt / 222);

	return 0;
}