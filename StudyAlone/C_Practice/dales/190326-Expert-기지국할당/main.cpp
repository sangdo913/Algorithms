#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CSIZE 5000
#define BIGLOSS 1000000000000

#ifdef _WIN32
#include <process.h>

#else
#include <pthread.h>

#endif

void test1(void* param);
void test2(void* param);

#ifndef _WIN32

void* threadFunc1(void* param) {
	test1(param);
	return 0;
}

void* threadFunc2(void* param) {
	test2(param);
	return 0;
}

#endif

int DONE;

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

	for (int c = 0; c < 4; )
	{
		int x = pseudo_rand() % CSIZE;
		int y = pseudo_rand() % CSIZE;

		if (CELL[y][x] != 0) continue;

		CB[y][x] = CELL[y][x] = -(c + 1); 

		NB[c][0] = x; 
		NB[c][1] = y; 
		c++;
	}

	for (int c = 0; c < 250000; ) 
	{
		int x = pseudo_rand() % CSIZE;
		int y = pseudo_rand() % CSIZE;

		if (CELL[y][x] != 0) continue; 
		CB[y][x] = CELL[y][x] = 1 + (pseudo_rand() % 4); 
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
			if ((CB[y][x] == 0) && (CELL[y][x] != 0) || 
				(CB[y][x] != 0) && (CELL[y][x] == 0))
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
}


int main(void)
{
	LOSS = 0.0;
	time_t start_time = clock();
	for (int c = 0; c < 10; c++)
	{
		build();
		DONE = 0;

#ifdef _WIN32
		_beginthread(test1, 0, (void*)CELL);
		_beginthread(test2, 0, (void*)CELL);

#else
		void *(*fp1)(void *) = threadFunc1;
		void *(*fp2)(void *) = threadFunc2;
		pthread_t p_thread[2];
		int ret;
		ret = pthread_create(&p_thread[0], NULL, fp1, (void *)CELL);
		if (ret < 0) {
			return -1;
		}

		ret = pthread_create(&p_thread[1], NULL, fp2, (void *)CELL);
		if (ret < 0) {
			return -1;
		}
#endif

		while (DONE == 0);
		calc();

#ifndef _WIN32
		pthread_join(p_thread[0], NULL);
		pthread_join(p_thread[1], NULL);
#endif
	}
	time_t end_time = clock();
	printf("Time : %d\n", (int)(end_time - start_time));
	printf("LOSS: %.1f (dB)\n", LOSS);
	return 0;
}
