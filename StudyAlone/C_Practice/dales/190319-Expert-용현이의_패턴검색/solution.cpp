#define SIZE 1024
#define NUM_QUERY 10000
#define SEGMENT_SIZE 16
#define NUM_PATTERN 4

#include <cstdio>

struct Coord{
	int y, x;
	Coord operator+(Coord c){ return {y + c.y, x + c.x }; }
	Coord operator-(Coord c){ return {y - c.y, x - c.x }; }
};

unsigned char map_copy[SIZE][SIZE];

template <class T, int T_SIZE = SIZE>
struct List {
	T 
}

Coord memo[5][40000];
int memoCnt[5];

struct Seg {
	Coord center;
	int center_num;

	Coord other[5][20];
	int otherCnt[5];

} seg[4];

void setCenter_0(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	for( int i = 0 ; i < SEGMENT_SIZE ; i++ )
		for( int j = 0 ; j < SEGMENT_SIZE ; j++ )
			if( segment[i][j] ){
				seg[0].center_num = segment[i][j];
				seg[0].center = {i, j};
				return;
			}
}

void setOther_0(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	for( int i = 0 ; i < SEGMENT_SIZE ; i++ ){
		for( int j = 0 ; j < SEGMENT_SIZE ; j++ ){
			if( segment[i][j] ){
				int num = segment[i][j];
				seg[0].other[num][seg[0].otherCnt[num]++] = {i - seg[0].center.y, j - seg[0].center.x};
			}
		}
	}
}

void setCenter_123(){
	Coord c = seg[0].center;
	seg[1].center = {SEGMENT_SIZE - c.y, c.x};
	seg[2].center = {SEGMENT_SIZE - c.y, SEGMENT_SIZE - c.x};
	seg[3].center = {c.y, SEGMENT_SIZE - c.x};;
}

void setOther_123(){
	for( int i = 1 ; i <= 4 ; i++ ){
		for( int j = 0 ; j < seg[0].otherCnt[i]; j++ ){
			Coord c = seg[0].other[i][j];
			seg[1].other[i][seg[1].otherCnt[i]++] = {-c.y, +c.x};
			seg[2].other[i][seg[2].otherCnt[i]++] = {-c.y, -c.x};
			seg[3].other[i][seg[3].otherCnt[i]++] = {+c.y, -c.x};
		}
	}
}

void setSegment(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	setCenter_0(segment);
	setOther_0(segment);

	setCenter_123();
	setOther_123();	
}

Coord findSegment(){


}


void init(unsigned char map[SIZE][SIZE]){
	for( int i = 1 ; i <= 4 ; i++ ) memoCnt[i] = 0;
	for( register int i = 0 ; i < SIZE ; i++ ){
		for( register int j = 0 ; j < SIZE ; j++ ){
			int val = map[i][j];
			map_copy[i][j] = val;
			if(val) memo[val][ memoCnt[val]++] = {i, j};
		}
	}
}


Coord findSegment(unsigned char segment[SEGMENT_SIZE][SEGMENT_SIZE]){
	Coord pos;
	pos.y = pos.x = 0;

	setSegment(segment);
	
	

	return pos;
}