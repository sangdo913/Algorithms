#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>


int board[10][10];

#define MISS		0
#define CARRIER		1
#define BATTLESHIP	2
#define CRUISER		3
#define SUBMARINE	4
#define DESTROYER	5

static int hit;
static const int len[5] = { 5, 4, 3, 3, 2 };

#define MAX_CALLCOUNT	10000

static int callcount;
static int limit;

int fire(int r, int c)
{
	if (r < 0 || r > 9 || c < 0 || c > 9 || callcount >= MAX_CALLCOUNT)
	{
		callcount = MAX_CALLCOUNT;
		return 0;
	}
	
	++callcount;
	
	int ret = board[r][c];
	
	if (board[r][c] > 0) --hit;
	board[r][c] = 0;
	
	return ret;
}
#include"user.cpp"

extern void init(int limit);
extern void play();
static int seed;

static int pseudo_rand()
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7fff;
}

static bool check(int r, int c, int d, int l)
{	
	if (d == 1)
	{
		for (int m = 0; m < l; ++m)
			if (board[r][c + m] > 0)
				return false;
		return true;
	}
	else
	{
		for (int m = 0; m < l; ++m)
			if (board[r + m][c] > 0)
				return false;
		return true;
	}
}

static void doarrangment()
{
	for (int r = 0; r < 10; ++r)
	for (int c = 0; c < 10; ++c)
		board[r][c] = 0;
	
	for (int k = 0; k < 5; ++k)
	{
		while(1)
		{
			int r, c, d;
			
			d = pseudo_rand() % 2;
			if (d == 1)
			{
				r = pseudo_rand() % 10;
				c = pseudo_rand() % (10 - len[k] + 1);
				if (check(r, c, d, len[k]))
				{
					for (int l = 0; l < len[k]; ++l)
						board[r][c + l] = k + 1;
					break;
				}
			}
			else
			{
				r = pseudo_rand() % (10 - len[k] + 1);
				c = pseudo_rand() % 10;
				if (check(r, c, d, len[k]))
				{
					for (int l = 0; l < len[k]; ++l)
						board[r + l][c] = k + 1;
					break;
				}
			}
		}
	}
}

int main()
{
	int TC;
	
    freopen("0Text.txt", "r", stdin);
	setbuf(stdout, NULL);
    scanf("%d", &TC);

	int totalscore = 0, totalcallcount = 0;
    for (int testcase = 1; testcase <= 10; ++testcase)
	{
		int score = 100, callcount4tc = 0;
		
		scanf("%d %d", &seed, &limit);
		
		init(limit);

		for (int g = 0; g < 10; ++g)
		{
			doarrangment();
		
			hit = 0;
			for (int k = 0; k < 5; ++k)
				hit += len[k];
		
			callcount = 0;
			play();

			if (hit != 0)
				callcount = MAX_CALLCOUNT;
			
			if (callcount > limit)
				score = 0;

			callcount4tc += callcount;
		}
		
		printf("#%d %d %d\n", testcase, score, callcount4tc);

		totalscore += score;
		totalcallcount += callcount4tc;
    }

    printf("avg : %lf\n", (double)totalcallcount / 100);
	printf("total score = %d, total callcount = %d\n", totalscore / TC, totalcallcount);
    return 0;
}