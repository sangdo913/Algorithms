#include <stdio.h>
#include <memory.h>
#include <time.h>

extern int encode(char*, char*, int);
extern void decode(char*, char*, int);

static unsigned long long seed = 5; // seed can be changed

static unsigned int random(void)
{
	return ((unsigned int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

static int  hit[26] = { 82, 15, 28, 43, 127, 22, 20, 61, 30, 2, 8, 40, 24, 67, 75, 19, 1, 60, 63, 91, 28, 10, 24, 2, 20, 1 };
static char dummy1[9999];
static char alpha[963];
static char dummy2[9998];
static char dic[1024][8];
static char dummy3[9997];
static int  dics[1024];
static int  papern;
static char src[65536];
static char dest[65536];
static char dummy4[2182];
static char paper[65536];
static char dummy5[291];
static char bak_paper[65536];
int mem[65536];
static void build_dic(void)
{
	int i = 0;
	int j = 0;

	for (int c = 0; c < 963; c++)
	{
		if (j >= hit[i])
		{
			i++;
			j = 0;
		}
		alpha[c] = 'a' + i;
		j++;
	}

	for (int c = 0; c < 1024; c++)
	{
		int l = 1 + random() % 7;
		dics[c] = l;
		for (int d = 0; d < l; d++)
			dic[c][d] = alpha[random() % 963];
	}
}

int main(void)
{
	int papern;

	build_dic();

	time_t TIME = clock();
	int    RATE = 0;

	for (int c = 0; c < 100; c++)
	{
		int pl = 0;

		while (true)
		{
			int i = random() % 1024;
			if (pl + dics[i] > 65535) break;

			for (int c = 0; c < dics[i]; c++)
				paper[pl++] = dic[i][c];

			paper[pl++] = ' ';
		}
		papern = pl;

		for (int i = 0; i < papern; i++)
		{
			bak_paper[i] = paper[i];
		}
		int s = encode(src, bak_paper, papern);

		for (int i = s; i < 65536; i++)
		{
			src[i] = 0;
		}

		decode(dest, src, s);

		if (memcmp(paper, dest, papern) != 0)
		{
			RATE += 10000000;
		}
		else
		{
			RATE += s;
		}
	}

	TIME = clock() - TIME;
	printf("SCORE: %.5f\n", RATE + TIME / 100000.);

}
