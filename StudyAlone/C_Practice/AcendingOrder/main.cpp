#include <cstdio>
const int SIZE = 5000000;
int mcopy[SIZE];
#include"user.cpp"
#include<time.h>
#include<stdlib.h>
// int TC;

const int MAX_NUM = 1000000000;
static int SCORE;
static int seed;

int arr[SIZE];

extern long long solve(int* arr, int n);

static int pseudo_rand(void) {
    seed = seed * 214013 + 2531011;
    return (seed >> 16) & 0x7FFF;
}

long long _build(int* arr, int n) {
    int prev = 0;
    long long ret = 0;
    for (register int i = 0; i < n; i++) {
        arr[i] = prev + (pseudo_rand()) % (MAX_NUM / SIZE + 1);
        prev = arr[i];
        if (i & 1)ret += arr[i];
    }
    return ret;
}

void _swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void _shuffle(int* arr, int n) {
    for (register int i = 0; i < n; i++) {
        register int a = -1, b = -1;
        while (a == b) {
            a = ((pseudo_rand() << 15) | pseudo_rand()) % SIZE;
            b = ((pseudo_rand() << 15) | pseudo_rand()) % SIZE;
        }
        _swap(arr[a], arr[b]);
    }
}

int main() {
    seed = 1235;
    // scanf("%d", &seed);
    SCORE = 0;
    clock_t TIME = 0;
    int TC = 10;
    for (int T = 0; T < TC; T++)
    {
        long long answer = _build(arr, SIZE);

        _shuffle(arr, SIZE);

        clock_t st = clock(), ed;
        long long result = solve(arr, SIZE);
        ed = clock();
        TIME += ed-st;

        if (answer == result) {
            printf("SUCESS\n");
                SCORE += 10;
        }
    }
    printf("RESULT : %d, time:%lf\n", SCORE, (double)(TIME)/CLOCKS_PER_SEC);
    return 0;
}

