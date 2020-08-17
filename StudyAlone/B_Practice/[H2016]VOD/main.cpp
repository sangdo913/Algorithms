#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"

#define GOTO	0
#define TICK	1

#define MAX_N				20000
#define MAX_M				128
#define MAX_BLOCKCOUNT		1250
#define MAX_DATALENGTH		5120000
#define FRAMESIZE			256


extern void Init(int N, int *size, unsigned char *data, int M, struct huffman *code);
extern void Goto(int frame);
extern int Tick(unsigned char *screen);


#if 0
struct huffman
{
	int symbol, codeword, codewordLength;
};
#endif

static int msize[MAX_BLOCKCOUNT];
int dummy1[80];
static unsigned char mdata[MAX_DATALENGTH];
int dummy2[3098];
static struct huffman code[MAX_M];
int dummy3[236];
static int point, expected;

#define THRESHOLD 0x07FFFFFF;
static int calcHash(unsigned char *screen, int len) {
	int ret = 0, p = 1;
	for (int x = 0; x < len; ++x)
	{
		ret += screen[x] * p++;
		ret &= THRESHOLD;
	}
	return ret;
}

static void sample_loadData(int *N, int *sizeArray, unsigned char *dataArray, int *M, struct huffman * code) {
	int i, t, Count;

	scanf("%d", N);

	scanf("%d", M);
	for (i = 0; i < *M; i++)
	{
		scanf("%d %d %d", &code[i].symbol, &code[i].codeword, &code[i].codewordLength);
	}

	scanf("%d", &Count);
	for (i = 0; i < Count; i++)
	{
		scanf("%d", &sizeArray[i]);
	}

	scanf("%d", &Count);
	for (i = 0; i < Count; i++)
	{
		scanf("%d", &t);
		dataArray[i] = (unsigned char)t;
	}
	point = 0;
}

static void loadData(int *N, int *sizeArray, unsigned char *dataArray, int *M, struct huffman * code) {
	int i, j,t, Count, n;
	int * d;

	unsigned char Blocks[16][4096];
	int BlockLen[16];

	d = (int *)dataArray;

	scanf("%d", N);

	scanf("%d", M);
	for (i = 0; i < *M; i++)
	{
		scanf("%d %d %d", &code[i].symbol, &code[i].codeword, &code[i].codewordLength);
	}
	
	scanf("%d", &Count);
	for (i = 0; i < Count; i++)
	{
		scanf("%d", &BlockLen[i]);
		for (j = 0; j < BlockLen[i]; j++)
		{
			scanf("%d", &t);
			Blocks[i][j] = (unsigned char)t;
		}
	}

	n = 0;
	scanf("%d", &Count);
	for (i = 0; i < Count; i++)
	{
		scanf("%d", &t);
		sizeArray[i] = BlockLen[t];
		for (j = 0; j < sizeArray[i]; j++)
			dataArray[n++] = Blocks[t][j];		
	}
	point = 0;
}


static void run() {
	int lineN, t = 0, frame, hash;
	int command, resultHash;
	unsigned char screen[FRAMESIZE];

	scanf("%d %d", &lineN, &expected);
	for (int line = 0; line < lineN; ++line)
	{
		scanf("%d", &command);
		switch (command) {
		case GOTO:
			scanf("%d", &frame);
			Goto(frame);
			break;
		case TICK:
			scanf("%d %d", &hash, &frame);
			t = Tick(screen);
			resultHash = calcHash(screen, FRAMESIZE);
			if (t == frame && resultHash == hash)
				point++;
            else 
                int debug = 1;
			break;
		default:
			break;
		}
	}
}

int main() {
	int T, N, M, totalScore;
	setbuf(stdout, NULL);
	freopen("0Text.txt", "r", stdin);

	scanf("%d", &T);
	totalScore = 0;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		if (testcase <= 5)
			sample_loadData(&N, msize, mdata, &M, code);
		else
			loadData(&N, msize, mdata, &M, code);

		Init(N, msize, mdata, M, code);
		run();
		printf("#%d %d\n", testcase, point);
		if (point == expected)
			totalScore++;
	}

	printf("total score = %d\n", totalScore * 100 / T);

	return 0;
}