#include<stdio.h>
#include<time.h>
typedef long long ll;

static int seed = 3;
static int dummy1[100];
static int dummy2[100];
static int dummy3[100];
static unsigned char KEY[200], key[200];
extern void test(unsigned char key[200]);

int pseudo_rand() {
    seed = seed * 214011 + 2531011;
    return (seed >> 16) & 0x7FFF;
}

int check(unsigned char key[200]) {
    int pos = 0, eq = 0;
    for (register int c = 0; c < 200; c++) {
        if (key[c] == KEY[c]) pos++;
    }
    for (register int c1 = 0; c1 < 200; c1++) {
        for (register int c2 = 0; c2 < 200; c2++) {
            if (key[c1] == KEY[c2]) eq++;
        }
    }
    return 256 * pos + eq;
}

void init() {
    int pool[256] = { 0 };

    for (int i = 0; i < 200; i++) {
        int val = pseudo_rand() % 255;
        while (pool[val] == 1) val = pseudo_rand() % 255;
        
        pool[val] = 1;
        KEY[i] = val + 1;
    }
}

int main()
{
    int RESULT = 0;
    for (int tc = 1; tc <= 50; tc++) {
        init();

        int st = clock();
        test(key);
        RESULT += (clock() - st) / (CLOCKS_PER_SEC / 1000);
        for (int i = 0; i < 200; i++) {
            if (key[i] != KEY[i]) RESULT += 10000;
        }
    }
    printf("RESULT : %d\n", RESULT);
}
