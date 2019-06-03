#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define MAXIMAGESIZE 1000
#define MAXSAMPLESIZE 50

unsigned char origin[MAXIMAGESIZE][MAXIMAGESIZE];
unsigned char image[2*MAXIMAGESIZE][2*MAXIMAGESIZE];
unsigned char sample[MAXSAMPLESIZE][MAXSAMPLESIZE];

struct Detect {
	int height, width;
};

/*
문제 설명.
N*N(최대 크기 1000*1000) 의 크기를 가지는 반도체가 있다.

이 반도체는 여러개가 나란히 인접해서 상하좌우로 이어져있으며,
반도체 마다 불량이 존재할 수 있다.

불량이 존재하면, 반도체 내에 최대 3*3 직사각형 구간의 값이 원본과 다르다.

엄청나게 많이 연결된 반도체 내에서, 일부 구간을 보여줄 것이다.
이 때 불량이 있다면 불량인 구간의 높이와 너비를 반환하고,
없으면 이 둘의 값을 0으로 해서 반환하면 된다.
*/


/*
void init(int N, int M) : 
10 <= N <= 1000
6 <= M <= 50
테스트케이스 시작시 한 번 호출
원래 이미지 크기인 N과 sample로 주는 크기인 M을 입력으로 준다.
*/
extern void init(int N, int M);
/*
void goodImage(unsigned char image[][MAXIMAGESIZE];
정상적인 이미지를 입력해준다
(최대 1000*1000). 

테스트케이스 초기화 마다 한 번 호출.
*/
extern void goodImage(unsigned char image[][MAXIMAGESIZE]);

/*
Detect sampleImage(unsigned char sample[][MAXAAMPLESIZE)
원본 이미지가 이어져있는 상태에서 일부분을 보여준다.
이 중에 최대 (3*3)의 직사각형 크기를 가지는 오염된 부분이 딱 1개 있거나, 
오염된 부분이 존재하지 않는다.

오염된 부분이 존재하면 오염된 부분의 가로 세로 길이를 반환한다.
오염된 부분이 없다면 가로 세로를 0으로 세팅해서 반환한다.
*/
extern Detect sampleImage(unsigned char sample[][MAXSAMPLESIZE]);

int Score;
int N, M, changedr,changedc,h,w;
int ns[51]= {0, 12, 15, 28, 31, 37, 44, 45, 51, 57, 71, 72, 77, 79, 79, 81, 88, 91, 101, 102, 105, 129, 137, 147, 241, 262, 273, 303, 323, 353, 422, 522, 646, 726, 788, 792, 822, 845, 859, 892, 977, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
int ms[51] = {0, 23, 46, 25, 24, 35, 26, 48, 47, 23, 42, 11, 13, 24, 24, 25, 28, 30, 42, 45, 47, 9, 12, 19, 20, 22, 27, 34, 35, 40, 48, 6, 7, 11, 12, 19, 26, 30, 38, 44, 48, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50 };

void setImage() {
		//int sr[] = { 0,0,N,N };
		//int sc[] = { 0,N,0,N };

		//for (int d = 0; d < 4; ++d) {
		//	for (int i = 0; i < N; ++i) {
		//		for (int j = 0; j < N; ++j) {
		//			image[sr[d]+i][sc[d]+j] = origin[i][j];
		//		}
		//	}
		//}

	for (int sr = 0; sr < N + M; sr+=N) {
		for (int sc = 0; sc < N + M; sc+=N) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					image[sr + i][sc + j] = origin[i][j];
				}
			}
		}
	}

	//for (int i = 0; i < N + M; ++i) {
	//	for (int j = 0; j < N + M; ++j) {
	//		printf("%3d ", image[i][j]);
	//	}
	//	printf("\n");
	//}

	//int debug = 1;
}

Detect ret;

Detect setSample() {

	ret.height = rand() % 4;
	ret.width = rand() % 4;

	h = rand() % N;
	w = rand() % N;
	//printf("%4d %4d\n", h, w);
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			sample[i][j] = image[h+ i][w + j];
		}
	}
	
	if (!ret.height || !ret.width) { ret.height = ret.width = 0; }
	else {
		changedr = rand() % (M - ret.height+1);
		changedc = rand() % (M - ret.width+1);

		for (int i = 0; i < ret.height; ++i) {
			for (int j = 0; j < ret.width; ++j) {
				if (!image[h + changedr + i][w + changedc + j]) {
					ret.height = ret.width = 0;
					return ret;
				}
			}
		}

		for (int i = 0; i < ret.height; ++i) {
			for (int j = 0; j < ret.width; ++j) {
				do {
					sample[changedr + i][changedc + j] = rand() % 256;
				} while (sample[changedr + i][changedc + j] == image[h + changedr + i][w + changedc + j]);
			}
		}
	}
	printf("before\n");
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%3d ", (int)sample[i][j]);
		}
		printf("\n");
	}
	int debug = 1;
	/*printf("before\n");
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%3d ", (int)sample[i][j]);
		}
		printf("\n");
	}
	printf("after\n");
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%3d ", (int)image[h + i][w + j]);
		}
		printf("\n");
	}

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%d ", sample[i][j] == image[h + i][w + j]);
		}
		printf("\n");
	}*/
	return ret;
}

void run(int tc) {
		Score = 1000;

		N = ns[tc];
		M = ms[tc];
		for (int i = 1; i < N; ++i) {
			for(int j = 1; j < N; ++j)
			origin[i][j] = rand() % 256;
		}

		for (int i = 0; i < N; ++i) {
			origin[i][N-1] = origin[N-1][i] = 0;
		}

		setImage();


		init(N,M);
		goodImage(origin);

		int queryNum = 500;

		while (queryNum--) {
			ret = setSample();
			Detect userans = sampleImage(sample);
			
			if (ret.height != userans.height || ret.width != userans.width) 
				Score = 0;
		}
}

//#include<fstream>
//#include<algorithm>
//using namespace std;

int main() {
	//ofstream fout;
	//fout.open("NS.txt");

	//for (int i = 40; i < 50; ++i) ns[i] = 1000, ms[i] = 50;
	//for (int i = 0; i < 20; ++i) {
	//	ns[i] = rand() % 100 +10;
	//	ms[i] = rand() % 45 + 6;
	//}

	//sort(ms + 10, ms + 20);
	//for (int i = 20; i < 30; ++i) {
	//	ns[i] = rand() % 500 + 100;
	//	ms[i] = rand() % 45 + 6;
	//}
	//sort(ms + 20, ms + 30);

	//for (int i = 30; i < 40; ++i) {
	//	ns[i] = rand() % 501 + 500;
	//	ms[i] = rand() % 45 + 6;
	//}
	//sort(ns, ns + 50);
	//sort(ms + 30, ms + 40);
	//fout << '{';
	//for (int i = 0; i < 50; ++i) {
	//	fout << ns[i] << ", " ;
	//}
	//fout << '\n';
	//fout << '{';
	//
	//for (int i = 0; i < 50; ++i) fout << ms[i] << ", ";
	//fout << '}';

	int T = 50;
	srand(time(0));
	
	clock_t allst = clock(), alled;
	int totalScore = 0;
	for (int tc = 1; tc <= T; ++tc) {
		clock_t  st = clock();
		run(tc);
		totalScore += Score;
		clock_t ed = clock();
		printf("#%2d: Score : %4d, time : %2.3lf\n", tc, Score, 1.0*(ed - st) / 1000);
	}
	alled = clock();
	printf("total Score : %4d\ntotal time: %2.3lf\n", totalScore, 1.0*(alled - allst) / 1000);
//	fout.close();

	return 0;
}