#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <memory.h>
#include <time.h>

#define MAX 4096

extern void recover(unsigned char map[MAX][MAX]);

static int seed = 3;  // seed can be changed
static unsigned char dummy1[256];  // dummy size can be changed
static unsigned char orgmap[MAX][MAX];
static unsigned char dummy2[256];
static unsigned char newmap[MAX][MAX];
static unsigned char dummy3[MAX];
static unsigned char xoverlap[MAX][MAX];
static unsigned char yoverlap[MAX][MAX];

bool check_map(unsigned char map[MAX][MAX])
{
	if (memcmp(orgmap, map, 16777216) == 0)
		return true;
	return false;
}

static int pseudo_rand(void)
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static bool line_check(int x1, int y1, int x2, int y2)
{
	if (x2 - x1 < 16) return false;
	if (y2 - y1 < 16) return false;
	if (memcmp(&xoverlap[y1][x1], dummy3, x2 - x1 + 1) != 0) return false;
	if (memcmp(&xoverlap[y2][x1], dummy3, x2 - x1 + 1) != 0) return false;
	if (memcmp(&yoverlap[x1][y1], dummy3, y2 - y1 + 1) != 0) return false;
	if (memcmp(&yoverlap[x2][y1], dummy3, y2 - y1 + 1) != 0) return false;
	return true;
}

static void draw_line(int x1, int y1, int x2, int y2)
{
	memset(&xoverlap[y1][x1], 1, x2 - x1 + 1);
	memset(&xoverlap[y2][x1], 1, x2 - x1 + 1);
	memset(&yoverlap[x1][y1], 1, y2 - y1 + 1);
	memset(&yoverlap[x2][y1], 1, y2 - y1 + 1);
}

static void draw_rect(void)
{
	int x1;
	int y1;
	int x2;
	int y2;
	int t;

	while (true)
	{
		x1 = 16 + (pseudo_rand() % 4064);
		y1 = 16 + (pseudo_rand() % 4064);
		x2 = 16 + (pseudo_rand() % 4064);
		y2 = 16 + (pseudo_rand() % 4064);

		if (x1 > x2)
		{
			t = x1;
			x1 = x2;
			x2 = t;
		}

		if (y1 > y2)
		{
			t = y1;
			y1 = y2;
			y2 = t;
		}

		if (line_check(x1, y1, x2, y2))
		{
			draw_line(x1, y1, x2, y2);
			break;
		}
	}

	int c = 1 + pseudo_rand() % 255;

	for (int x = x1; x <= x2; x++) orgmap[y1][x] = c;
	for (int x = x1; x <= x2; x++) orgmap[y2][x] = c;
	for (int y = y1; y <= y2; y++) orgmap[y][x1] = c;
	for (int y = y1; y <= y2; y++) orgmap[y][x2] = c;
}

static void build_map(void)
{
	memset(orgmap, 0, 16777216);

	memset(xoverlap, 0, 16777216);
	memset(yoverlap, 0, 16777216);

	for (int c = 0; c < 1024; c++)
		draw_rect();

	memcpy(newmap, orgmap, 16777216);

	for (int c = 0; c < 256; c++)
	{
		int x1 = pseudo_rand() % 16;
		int y1 = pseudo_rand() % 16;
		int x2 = pseudo_rand() % 16;
		int y2 = pseudo_rand() % 16;

		for (int cy = 0; cy < 256; cy++)
		{
			memcpy(dummy1, &newmap[y1 * 256 + cy][x1 * 256], 256);
			memcpy(&newmap[y1 * 256 + cy][x1 * 256], &newmap[y2 * 256 + cy][x2 * 256], 256);
			memcpy(&newmap[y2 * 256 + cy][x2 * 256], dummy1, 256);
		}
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	printf("RESULT\n");

	int result = 1000000;

	memset(dummy3, 0, MAX);

	for (register int T = 0; T < 10; T++)
	{
		build_map();
		time_t START = clock();
		recover(newmap);
		result += (int)((clock() - START) / (CLOCKS_PER_SEC / 1000));
		if (check_map(newmap))
			result -= 100000;
		printf("%2d : %6d\n", T + 1, result);
	}

	return 0;
}