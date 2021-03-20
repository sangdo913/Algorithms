/*
cut :	44418734 (maybe)
 */
int T;
#include <iostream>
#include <ctime>
#include"user.cpp"

using namespace std;

void test(int trash_map[1000][1000]);

static int seed = 2;  // the seed will be changed
static int result = 0;
static int dummy0[222];
static int trash_map[1000][1000];
static int dummy1[333];
int ori_trash_map[1000][1000];
static int dummy2[444];
static int trash_can[3];

static int pseudo_rand(void)
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static void build_map(void)
{
	for (int y = 0; y < 1000; y++)
		for (int x = 0; x < 1000; x++)
			trash_map[y][x] = 0;

	int c;
	for (c = 0; c < 10000;)
	{
		int x = pseudo_rand() % 1000;
		int y = pseudo_rand() % 1000;

		if (trash_map[y][x] == 0)
		{
			trash_map[y][x] = -1; // trash
			c++;
		}
	}
	// printf("c:%d\n", c);

	for (int c = 1; c <= 3;)
	{
		int x = pseudo_rand() % 1000;
		int y = pseudo_rand() % 1000;

		if (trash_map[y][x] == 0)
		{
			trash_map[y][x] = c; // trash_can
			c++;
		}
	}

	trash_can[0] = trash_can[1] = trash_can[2] = 0;

	for (int y = 0; y < 1000; y++)
		for (int x = 0; x < 1000; x++)
			ori_trash_map[y][x] = trash_map[y][x];
}

void move_trash(int y, int x, int d)
{
	//    cout << "m";
	if (result == 1000000000) return;

	result++;

	int ox = x;
	int oy = y;

	switch (d)
	{
	case 0: y--; break;
	case 1: y++; break;
	case 2: x--; break;
	case 3: x++; break;
	}

	if ((x < 0) || (x >= 1000) || (ox < 0) || (ox >= 1000)) {

	}
	if ((y < 0) || (y >= 1000) || (oy < 0) || (oy >= 1000)) {

	}

	if (ori_trash_map[y][x] == -1) {
		int wrong=1;

	}
	if (ori_trash_map[oy][ox] != -1)
	{
		int wrong=1;

	}

	if (ori_trash_map[y][x] == 0)
	{
		ori_trash_map[oy][ox] = 0;
		ori_trash_map[y][x] = -1;
	}
	else
	{
		int i = ori_trash_map[y][x] - 1;

		if (trash_can[i] == 3500) {
			return;
		}
		// printf("to (%d %d)\n", oy,ox);

		ori_trash_map[oy][ox] = 0;
		trash_can[i]++;
	}
}

int resutl1;

int main(void)
{
	for ( T = 0; T < 10; T++)
	{
		printf("T:%d\n", T);
		build_map();

		time_t START = clock();
		test(trash_map);
		result += ((clock() - START) / (CLOCKS_PER_SEC / 1000));

		int tnum = 0;
		for (int y = 0; y < 1000; y++)
			for (int x = 0; x < 1000; x++)
				if (ori_trash_map[y][x] == -1){
					result += 10000;
					tnum++;
				}
		 printf("%d\n", tnum);
	}

	cout << "RESULT : " << result << endl;

	return 0;
}
