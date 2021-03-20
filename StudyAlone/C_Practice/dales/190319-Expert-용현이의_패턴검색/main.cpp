#include <cstdio>
#include <ctime>

#define SIZE 1024
#define NUM_QUERY 10000
#define SEGMENT_SIZE 16
#define NUM_PATTERN 4

#define PENALTY 1000

struct Coord{
	int y, x;
};

static int seed = 1105;
static int pseudo_rand(void){
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static unsigned char _map[SIZE][SIZE];
static unsigned char _segment[SEGMENT_SIZE][SEGMENT_SIZE];
static unsigned char _tmp[SEGMENT_SIZE][SEGMENT_SIZE];

extern void init(unsigned char map[SIZE][SIZE]);
extern Coord findSegment(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]);

void _build(unsigned char map[SIZE][SIZE]){
	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++){
			if (pseudo_rand() % 8 == 0)
				map[y][x] = pseudo_rand() % NUM_PATTERN + 1;
			else
				map[y][x] = 0;
		}
}


void flip_updown(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	for (int x = 0; x < SEGMENT_SIZE; x++)
		for (int y = 0; y < SEGMENT_SIZE / 2; y++){
			int tmp = segment[y][x];
			segment[y][x] = segment[SEGMENT_SIZE - y - 1][x];
			segment[y][x] = tmp;
		}
}

void flip_leftright(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	for (int y = 0; y < SEGMENT_SIZE; y++)
		for (int x = 0; x < SEGMENT_SIZE / 2; x++){
			int tmp = segment[y][x];
			segment[y][x] = segment[y][SEGMENT_SIZE - x - 1];
			segment[y][x] = tmp;
		}
}

int main(){
	int T = 10;;
	int SCORE = 0;
	for (int t = 0; t < T; t++){
		_build(_map);

		time_t START = clock();
		init(_map);
		for (int q = 0; q < NUM_QUERY; q++){
			int sy = pseudo_rand() % (SIZE - SEGMENT_SIZE + 1);
			int sx = pseudo_rand() % (SIZE - SEGMENT_SIZE + 1);

			for (int y = 0; y < SEGMENT_SIZE; y++)
				for (int x = 0; x < SEGMENT_SIZE; x++){
					_segment[y][x] = _map[sy + y][sx + x];
				}

			if (pseudo_rand() % 4 == 0)
				flip_leftright(_segment);
			if (pseudo_rand() % 4 == 0)
				flip_updown(_segment);

			Coord pos = findSegment(_segment);

			if (pos.x != sx || pos.y != sy) SCORE += PENALTY;
		}
		SCORE += (int)((clock() - START) / (CLOCKS_PER_SEC / 1000));
	}

	printf("%d\n", SCORE);
	if (SCORE <= 5000)
		return 0;
	else
		return -1;
}