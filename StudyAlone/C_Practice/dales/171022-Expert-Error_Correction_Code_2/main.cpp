#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int TC = 1023;

unsigned char orig[TC][4096];
unsigned char data[TC][256][32] = { 0, };
unsigned char res[TC][4096];

unsigned char getpixel(unsigned char dat[256][32], int x, int y);
void setpixel(unsigned char dat[256][32], int x, int y, unsigned char val);

extern void encode(unsigned char inp[4096], unsigned char dat[256][32]);
extern void decode(unsigned char dat[256][32], unsigned char out[4096]);

unsigned char getpixel(unsigned char dat[256][32], int x, int y) {
	unsigned char mask = 0x80 >> (x % 8);
	return (dat[y][x / 8] & mask) > 0;
}

void setpixel(unsigned char dat[256][32], int x, int y, unsigned char set) {
	unsigned char mask = 0x80 >> (x % 8);
	if (set) dat[y][x / 8] |= mask;
	else 	 dat[y][x / 8] &= ~mask;
}

void errInjection(unsigned char dat[256][32]) {
	for (int y = 0; y < 256; y = y + 2) {
		for (int x = 0; x < 256; x = x + 2) {
			setpixel(dat, x + (rand() % 2), y + (rand() % 2), 0);
			setpixel(dat, x + (rand() % 2), y + (rand() % 2), 1);
		}
	}
}

void randRotation(unsigned char dat[256][32], int rot) {
	unsigned char buf[256][32];

	switch (rot) {
	case 0:
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, x, y, getpixel(dat, x, y));
		break;
	case 1:
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, 255 - y, x, getpixel(dat, x, y));
		break;
	case 2:
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, 255 - x, 255 - y, getpixel(dat, x, y));
		break;
	case 3:
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, y, 255 - x, getpixel(dat, x, y));
		break;
	}

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 32; j++)
			dat[i][j] = buf[i][j];

}

void randFliping(unsigned char dat[256][32], int flip) {
	unsigned char buf[256][32];

	switch (flip) {
	case 0:
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, x, y, getpixel(dat, x, y));
		break;
	case 1: // horizen flip
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, 255 - x, y, getpixel(dat, x, y));
		break;
	case 2: // vertical flip
		for (int y = 0; y < 256; y++)
			for (int x = 0; x < 256; x++)
				setpixel(buf, x, 255 - y, getpixel(dat, x, y));
		break;
	}

	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 32; j++)
			dat[i][j] = buf[i][j];

}

int main() {

	int PERFORMANCE = 10000;
	srand(3);

	// generate random data;
	for (int i = 0; i < TC; i++) {
		for (int j = 0; j < 4096; j++) {
			orig[i][j] = rand() % 15;
		}
	}

	// TEST

	time_t start_enc = clock();
	for (int i = 0; i < TC; i++) {
		encode(orig[i], data[i]);
	}
	time_t end_enc = clock();
	printf("Encoding time : %d\n", (int)(end_enc - start_enc));
	PERFORMANCE -= (int)(end_enc - start_enc);

	time_t start_err = clock();
	for (int i = 0; i < TC; i++) {
		errInjection(data[i]);
		randRotation(data[i], rand() % 4);
		randFliping(data[i], rand() % 3);
	}
	time_t end_err = clock();
	printf("Err inj  time : %d\n", (int)(end_err - start_err));

	time_t start_dec = clock();
	for (int i = 0; i < TC; i++) {
		decode(data[i], res[i]);
	}
	time_t end_dec = clock();
	printf("Decoding time : %d\n", (int)(end_dec - start_dec));
	PERFORMANCE -= (int)(end_dec - start_dec);

	for (int i = 0; i < TC; i++) {
		if (memcmp(orig[i], res[i], 4096 * sizeof(unsigned char)) == 0) {
			PERFORMANCE += 10000;
		}
	}

	printf("Performance : %d\n", PERFORMANCE);

	return 0;
}