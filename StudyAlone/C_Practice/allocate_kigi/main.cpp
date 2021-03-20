#include <stdio.h>
#include<cstdio>
#include <ctime>
#include <stdlib.h>
#include <math.h>

void test(void* param);

#define CSIZE 5000
#define BIGLOSS 50000000
#include"user.cpp"

static char CELL[CSIZE][CSIZE];
static char CB[CSIZE][CSIZE];
static int NB[4][2];
static double LOSS;

static int seed = 3;

static int pseudo_rand(void)
{
	seed = seed * 214011 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static void build(void)
{
	for (int y = 0; y < CSIZE; y++)
		for (int x = 0; x < CSIZE; x++)
			CB[y][x] = CELL[y][x] = 0;

	for (int c = 0; c < 4;)
	{
		int x = pseudo_rand() % CSIZE;
		int y = pseudo_rand() % CSIZE;

		if (CELL[y][x] != 0) continue;

		CB[y][x] = CELL[y][x] = -(c + 1);

		NB[c][0] = x;
		NB[c][1] = y;
		c++;
	}

	for (int c = 0; c < 250000;)
	{
		int x = pseudo_rand() % CSIZE;
		int y = pseudo_rand() % CSIZE;

		if (CELL[y][x] != 0) continue;
		CB[y][x] = CELL[y][x] = 1 + (pseudo_rand() % 4); \
			c++;
	}
}

static void calc(void)
{
	int NBUE[4] = { 0 };

	for (int c = 0; c < 4; c++)
		if (CELL[NB[c][1]][NB[c][0]] >= 0)
			LOSS += BIGLOSS;

	for (int y = 0; y < CSIZE; y++)
		for (int x = 0; x < CSIZE; x++)
		{
			if (CB[y][x] < 0) continue;
			if ((CELL[y][x] < 0 || CELL[y][x] > 4) ||
				(CB[y][x] == 0 && CELL[y][x] != 0) ||
				(CB[y][x] != 0 && CELL[y][x] == 0))
				LOSS += BIGLOSS;

			if ((1 <= CELL[y][x]) && (CELL[y][x] <= 4))
			{
				int i = CELL[y][x] - 1;
				int dx = NB[i][0] - x;
				int dy = NB[i][1] - y;

				LOSS += dx * dx + dy * dy;
				NBUE[i]++;
			}
		}

	if (NBUE[0] + NBUE[1] + NBUE[2] + NBUE[3] != 250000)
		LOSS += BIGLOSS;

	for (int c = 0; c < 4; c++)
		if (NBUE[c] > 67500)
			LOSS += (NBUE[c] - 67500) * (double)50000000;
    for(int i= 0; i < 4; ++i){
        if(NBUE[i] != clilen[i+1]){
            printf("wrong\n");
        }
    }
}

int main(void)
{
	int tc = 10;
	//scanf("%d", &tc);
	clock_t start = clock();
	LOSS = 0.0;
	for (int c = 0; c < tc; c++)
	{
		build();
		test((void*)CELL);
		calc();
	}

	if (LOSS <= 6800000000000.0) {
		printf("PASS diff : %lf\n", 6800000000000.0- LOSS);
		printf("LOSS: %.1f (dB)\n", LOSS);
	}
	else {
		printf("LOSS: %.1f (dB)\n", LOSS);
		printf("DIFF: %.1f (dB)\n", LOSS - 6800000000000.0);
		printf("TIME : %f seconds.\n", ((float)(clock() - start) / CLOCKS_PER_SEC));
	}
	return 0;
}
