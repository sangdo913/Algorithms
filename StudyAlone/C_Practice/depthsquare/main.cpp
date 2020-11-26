#include <cstdio>
#include<string>
#include<fstream>
#include"user.cpp"
using namespace std;
#define SIZE 100
const int NUM_RECT = 64;
const int MIN_RECT_SIZE = 10;
int COUNT, SCORE;
int seed = 1117;

int image[SIZE][SIZE];
extern int recog(int image[SIZE][SIZE]);
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
		if (ex - sx < MIN_RECT_SIZE) continue;
		if (ey - sy < MIN_RECT_SIZE) continue;
		break;
	}
	int height = pseudo_rand()%5 + 1;
	for (register int y = sy; y <= ey; y++)
		for (register int x = sx; x <= ex; x++)
			image[y][x] += height;
	if (ex - sx == ey - sy) 
		COUNT++;
}

void _build() {
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			image[y][x] = 0;
	COUNT = 0;
	for (int i = 0; i < NUM_RECT; i++) rect();
}

int main() {
	//scanf("%d", &seed);
    seed = 1117;
	SCORE = 0;
	for (int T = 0; T < 10; T++)
	{
		_build();
		 if(T%30){
			printf("%d\n", T);
		 }
		//printf("%d\n", COUNT);
		
		int ret = recog(image);
		ofstream f("0Text.txt");
		for(int i = 0;  i< SIZE; ++i){
			for(int j = 0; j < SIZE; ++j){
				string s = to_string(image[i][j]);
				while(s.size() < 2) s.push_back('X');
				f << s << ' ';
			}
			f << '\n';
		}
		if ( ret == COUNT) {
			SCORE++;	
		}
		else{
			int x = 1;
			printf("%d\n", ret);
			// printf("wrong!\n");
		}
	}

	printf("score: %d\n", SCORE);
	if (SCORE >= 2700)
		printf("PASS\n");
	else
		printf("FAIL\n");
	//printf("RESULT: %d\n", SCORE);

	return 0;
}