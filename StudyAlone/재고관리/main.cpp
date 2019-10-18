#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int MAX_ITEM = 1000000;
static int seed = 3;
static int pseudo_rand(void) {
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}


struct ITEM
{
	int version;	// 1 ~ 10
	int price;	// 100000 ~ 1999999
	int cores;	// 1 ~ 8
	double size; // 1.0 ~ 5.0

	ITEM()
	{
		this->version = 1 + (pseudo_rand() % 10);
		this->price = 100000 + (pseudo_rand() % 1900000);
		this->cores = 1 + (pseudo_rand() % 8);
		this->size = (10000 + (pseudo_rand() % 40001)) / 10000.0;
	}
};

struct RANGE_INT
{
	int from;
	int to;
};

struct RANGE_DBL {
	double from;
	double to;
};

extern void init();
extern void produce(const ITEM& item);
extern int search(RANGE_INT version, RANGE_INT price, RANGE_INT cores, RANGE_DBL size);

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	seed = 3;

	int PERFORMANCE = 0;
	int ans;
	int order_number = -1;

	for (register int TRY = 1; TRY <= 10; TRY++)
	{
		time_t start = clock();
		init();

		for (register int c = 1; c <= MAX_ITEM; c++)
		{
			produce(ITEM());
			if (c % 10000 == 0 && 500000 <= c) {
				RANGE_INT version, price, cores;
				RANGE_DBL size;

				version.from = 1 + (pseudo_rand() % 10);
				version.to = 1 + (pseudo_rand() % 10);
				if (version.from > version.to) {
					int tmp = version.from;
					version.from = version.to;
					version.to = tmp;
				}

				price.from = 100000 + (pseudo_rand() % 1900000);
				price.to = 100000 + (pseudo_rand() % 1900000);
				if (price.from > price.to) {
					int tmp = price.from;
					price.from = price.to;
					price.to = tmp;
				}

				cores.from = 1 + (pseudo_rand() % 8);
				cores.to = 1 + (pseudo_rand() % 8);
				if (cores.from > cores.to) {
					int tmp = cores.from;
					cores.from = cores.to;
					cores.to = tmp;
				}

				size.from = (10000 + (pseudo_rand() % 40001)) / 10000.0;
				size.to = (10000 + (pseudo_rand() % 40001)) / 10000.0;
				if (size.from > size.to) {
					double tmp = size.from;
					size.from = size.to;
					size.to = tmp;
				}

				scanf("%d", &ans);
				int sol = search(version, price, cores, size);
				if (sol != ans) PERFORMANCE += 1000;
			}
		}
		PERFORMANCE += ((clock() - start) / (CLOCKS_PER_SEC / 1000));
	}
	if (PERFORMANCE <= 5000)
		printf("PASS\n");
	else
		printf("PERFORMANCE = %d\n", PERFORMANCE);

	return 0;
}