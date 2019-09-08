#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"user.cpp"

#define MAX_TEST_CASE		50
#define MIN_CHIP_SIZE		10
#define MAX_CHIP_SIZE		1000
#define MIN_SAMPLE_SIZE		6
#define MAX_SAMPLE_SIZE		50
#define MIN_DEFECT_SIZE		1
#define MAX_DEFECT_SIZE		3

#define DEFECT_RATIO		0.9

// extern struct Rect
// {
// 	unsigned int width;		// First dimension
// 	unsigned int height;	// Second dimension
// };

extern void init(unsigned int m, unsigned int n);
extern void setChipImage(unsigned char **chipImage);
extern Rect checkSampleImage(unsigned char **sampleImage);

void generateChipImage(unsigned char **chip_image, unsigned int chip_size)
{
	unsigned int chip_size_with_border = chip_size + 2;
	unsigned int border_x1 = rand() % chip_size_with_border;
	unsigned int border_x2 = (border_x1 + 1) % chip_size_with_border;
	unsigned int border_y1 = rand() % chip_size_with_border;
	unsigned int border_y2 = (border_y1 + 1) % chip_size_with_border;

	for (volatile unsigned int i = 0; i < chip_size_with_border; i++)
		for (volatile unsigned int j = 0; j < chip_size_with_border; j++)
			chip_image[i][j] = (rand() % 255) + 1;

	for (volatile unsigned int i = 0; i < chip_size_with_border; i++)
		chip_image[i][border_x1] = 0;
	for (volatile unsigned int i = 0; i < chip_size_with_border; i++)
		chip_image[i][border_x2] = 0;
	for (volatile unsigned int i = 0; i < chip_size_with_border; i++)
		chip_image[i][border_y1] = 0;
	for (volatile unsigned int i = 0; i < chip_size_with_border; i++)
		chip_image[i][border_y2] = 0;
}

void copyChipImage(unsigned char **origin_chip_image, unsigned char **chip_image, unsigned int x, unsigned int y, unsigned int copy_size)
{
	for (volatile unsigned int i = 0; i < copy_size; i++)
		for (volatile unsigned int j = 0; j < copy_size; j++)
			chip_image[i][j] = origin_chip_image[i + x][j + y];
}

void generateDefect(unsigned char **chip_image, unsigned int chip_size, Rect *defectRect)
{
	unsigned int x, y;
	unsigned char origin;

	defectRect->width = (rand() % 3) + 1;
	defectRect->height = (rand() % 3) + 1;
	x = rand() % (chip_size - defectRect->width + 1);
	y = rand() % (chip_size - defectRect->height + 1);
	for (volatile unsigned int i = 0; i < defectRect->width; i++)
	{
		for (volatile unsigned int j = 0; j < defectRect->height; j++)
		{
			origin = chip_image[i + x][j + y];
			while (origin == chip_image[i + x][j + y])
				chip_image[i + x][j + y] = rand() % 256;
		}
	}
}

int main(void)
{
	unsigned int total_score, score;
	unsigned int m, n;
	unsigned int x, y;
	unsigned char **origin_chip_image;
	unsigned char **sample_chip_image;
	Rect defectRect, userRect;
    freopen("0Text.txt", "r", stdin);
	clock_t start;

	origin_chip_image = (unsigned char **)malloc(sizeof(unsigned char *) * (MAX_CHIP_SIZE + 2));
	for (volatile unsigned int i = 0; i < MAX_CHIP_SIZE + 2; i++)
		origin_chip_image[i] = (unsigned char *)malloc(sizeof(unsigned char) * (MAX_CHIP_SIZE + 2));

	sample_chip_image = (unsigned char **)malloc(sizeof(unsigned char *) * MAX_SAMPLE_SIZE);
	for (volatile unsigned int i = 0; i < MAX_SAMPLE_SIZE; i++)
		sample_chip_image[i] = (unsigned char *)malloc(sizeof(unsigned char) * MAX_SAMPLE_SIZE);

	srand(0);

    clock_t st = clock();
	total_score = 0;
	for (volatile int T = 1; T <= MAX_TEST_CASE; T++)
	{
		m = n = (rand() % (MAX_CHIP_SIZE - MIN_CHIP_SIZE + 1)) + MIN_CHIP_SIZE;
		while (m >= n)
			m = (rand() % (MAX_SAMPLE_SIZE - MIN_SAMPLE_SIZE + 1)) + MIN_SAMPLE_SIZE;

		generateChipImage(origin_chip_image, n);

		x = rand() % (n - m + 3);
		y = rand() % (n - m + 3);

		copyChipImage(origin_chip_image, sample_chip_image, x, y, m);

		defectRect.width = 0;
		defectRect.height = 0;
		if ((rand() % 10) < DEFECT_RATIO * 10)
			generateDefect(sample_chip_image, m, &defectRect);

		start = clock();

		// Solve problem
		init(m, n);
		setChipImage(origin_chip_image);
		userRect = checkSampleImage(sample_chip_image);

		// 0.1 sec == 1000 score
		score = (unsigned int)((float)(clock() - start) * 10000 / CLOCKS_PER_SEC);
		if (userRect.width == defectRect.width && userRect.height == defectRect.height)
			total_score += score;
		else
			total_score += 10000;
	}

	for (volatile unsigned int i = 0; i < MAX_SAMPLE_SIZE; i++)
		free(sample_chip_image[i]);
	free(sample_chip_image);

	for (volatile unsigned int i = 0; i < MAX_CHIP_SIZE + 2; i++)
		free(origin_chip_image[i]);
	free(origin_chip_image);

    printf("time : %lf\n", (clock()*1.0 - st)/CLOCKS_PER_SEC*1.0);
	if (total_score <= 1000 * MAX_TEST_CASE)
		printf("Pass\n");
	else
		printf("total score : %d\nFail\n", total_score);

	return 0;
}