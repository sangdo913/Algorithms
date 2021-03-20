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
int rects[SIZE][SIZE];

int square[SIZE*SIZE][4];
int slen;

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
	if (ex - sx == ey - sy) {
		square[COUNT][0] = sx;
		square[COUNT][1] = sy;
		square[COUNT][2] = ex;
		square[COUNT][3] = ey;
		COUNT++;
	}
}

void _build() {
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			image[y][x] = 0;
	COUNT = 0;
	for (int i = 0; i < NUM_RECT; i++) rect();
}

void print_file(fstream& f){
	return;
		for(int i = 0; i <SIZE; ++i) {
			for(int j = 0; j < SIZE; ++j){
				string n;
				int v= image[i][j];
				int cnt = 0;
				while(v){
					cnt++;
					v/=10;
				}
				if(cnt == 0) cnt = 1; 
				string s;
				cnt = 3-cnt;
				while(cnt--) s.push_back('_');
				n = s + to_string(image[i][j]);
				f << n << ' ';
			}
			f << '\n';
		}
}
int main() {
	fstream f("1Text.txt");
	//scanf("%d", &seed);
    seed = 1117;
	SCORE = 0;
	for (int T = 0; T < 3000; T++) {
		_build();
		// printf("%d\n", COUNT);
		// if(COUNT>1){
		// 	for(int i = 0; i < SIZE; ++i){
		// 		for(int j = 0; j < SIZE; ++j){
		// 			f << rects[i][j] << ' ';
		// 		}
		// 		f << '\n';
		// 	}
		// }
		
		int ret = recog(image);
		if (ret == COUNT) {
			SCORE++;	
		}
		else{
			// printf("ret: %d correct: %d\n", ret,COUNT);
			// for(int i = 0; i < COUNT; ++i){
			// 	printf("(%d %d) (%d %d)\n",square[i][0], square[i][1], square[i][2], square[i][3]);
			// }
			// printf("\n");
			print_file(f);
			int x =1;
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