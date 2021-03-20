#ifdef _WIN32
#include <cstdlib>
#include<ctime>
#include"user.cpp"
#else
#include <unistd.h>
#endif
#include <cstdio>


//const int SIZE = 64;
int COUNT, SCORE;
int seed = 1117;

unsigned char image[SIZE][SIZE];

extern int recog(unsigned char image[SIZE][SIZE]);
static int pseudo_rand(void){
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

void rect() {
	int sx, sy, ex, ey, tmp;
	while (true) {
		sx = pseudo_rand() % SIZE;
		ex = pseudo_rand() % SIZE;
		sy = pseudo_rand() % SIZE;
		ey = pseudo_rand() % SIZE;

		if (sx > ex) {
			tmp = sx;
			sx = ex;
			ex = tmp;
		}

		if (sy > ey) {
			tmp = sy;
			sy = ey;
			ey = tmp;
		}
		if (ex - sx < 9) continue;
		if (ey - sy < 9) continue;
		break;
	}
	for (register int y = sy; y <= ey; y++)
		for (register int x = sx; x <= ex; x++)
			image[y][x]++;
	if (ex - sx == ey - sy)
		COUNT++;

}

void _build() {
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			image[y][x] = 0;
	COUNT = 0;
	for (int i = 0; i < 50; i++) rect();
}

int main() {
    seed = 1117;
	// scanf("%d", &seed); // should be 1117 you can remove this in development mode
	SCORE = 0;
    clock_t st = clock();
	for (int T = 0; T < 10000; T++)
	{
		_build();
		if (recog(image) == COUNT) SCORE++;
	}
	#ifdef _WIN32
	_sleep(10000 - SCORE);
	#else
	usleep((10000 - SCORE)*1000);
	#endif
	printf("DONE\n");
	printf("RESULT: %d\n", SCORE); // you can measure your score by uncommenting this.
    printf("%lf\n", 1.0*(clock()-st)/CLOCKS_PER_SEC);
	return 0;
}
