#include <stdio.h>
#include <memory.h>
#include <time.h>
#include<fstream>
int convpuzzle[16][16];
int originpuzzle[16][16];
#define MAX 4096
#include "user.cpp"
using namespace std;


extern void recover(unsigned char map[MAX][MAX]);

static int seed = 1105;
static unsigned char keep1[256]; 
static unsigned char keep2[MAX];
static unsigned char newmap[MAX][MAX];
static unsigned char xoverlap[MAX][MAX];
static unsigned char yoverlap[MAX][MAX];

static unsigned char orgmap[MAX][MAX];
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
	if (memcmp(&xoverlap[y1][x1], keep2, x2 - x1 + 1) != 0) return false;
	if (memcmp(&xoverlap[y2][x1], keep2, x2 - x1 + 1) != 0) return false;
	if (memcmp(&yoverlap[x1][y1], keep2, y2 - y1 + 1) != 0) return false;
	if (memcmp(&yoverlap[x2][y1], keep2, y2 - y1 + 1) != 0) return false;
	return true;
}

static void draw_line(int x1, int y1, int x2, int y2)
{
	memset(&xoverlap[y1][x1], 1, x2 - x1 + 1);
	memset(&xoverlap[y2][x1], 1, x2 - x1 + 1);
	memset(&yoverlap[x1][y1], 1, y2 - y1 + 1);
	memset(&yoverlap[x2][y1], 1, y2 - y1 + 1);
}

void printmap(void){
	for(int i = 0; i < 16; ++i){
		for(int j = 0; j < 16; ++j){
			int id = originpuzzle[i][j];
			convpuzzle[id/16][id%16] = i*16+j;
		}
	}
	for(int i = 0;i < 16; ++i){
		for(int j = 0; j < 16; ++j){
			printf("%3d ", convpuzzle[i][j]);
		}
		printf("\n");
	}
	return;
    for(int i = 0; i < MAX; ++i){
        for(int j = 0; j < MAX; ++j){
            printf("%3d ", orgmap[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
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
	for(int i = 0; i < 256; ++i){
		originpuzzle[i/16][i%16] = i;
	}

	for (int c = 0; c < 256; c++)
	{
		int x1 = pseudo_rand() % 16;
		int y1 = pseudo_rand() % 16;
		int x2 = pseudo_rand() % 16;
		int y2 = pseudo_rand() % 16;
		int t = originpuzzle[y1][x1];
		originpuzzle[y1][x1] = originpuzzle[y2][x2];
		originpuzzle[y2][x2] = t;

		for (int cy = 0; cy < 256; cy++)
		{
			memcpy(keep1, &newmap[y1 * 256 + cy][x1 * 256], 256);
			memcpy(&newmap[y1 * 256 + cy][x1 * 256], &newmap[y2 * 256 + cy][x2 * 256], 256);
			memcpy(&newmap[y2 * 256 + cy][x2 * 256], keep1, 256);
		}
	}
}

int main(void)
{
	int tc = 20;
	// scanf("%d", &tc);
	setbuf(stdout, NULL);
	int result = 2000000;
	memset(keep2, 0, MAX);
	time_t st = clock();
	for (register int T = 0; T < tc; T++)
	{
		build_map();
		time_t START = clock();
        // printmap();
		recover(newmap);
		result += (int)((clock() - START) / (CLOCKS_PER_SEC / 1000));
		if (check_map(newmap)){
			printf("SUCCESS\n");

			result -= 100000;
		}
		else printf("fail\n");
	}
	if (result < 6000)
		printf("PASS\n");
	else
		printf("RESULT: %d\n", result);
	printf("%lf\n", 1.0*(clock()-st)/CLOCKS_PER_SEC);
	return 0;
}