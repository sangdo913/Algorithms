#define SIZE 1024
#define NUM_QUERY 10000
#define SEGMENT_SIZE 16
#define NUM_PATTERN 4

struct Coord{
	int y, x;
};

void init(unsigned char map[SIZE][SIZE]){


}

Coord findSegment(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	Coord pos;
	pos.y = pos.x = 0;
	return pos;
}