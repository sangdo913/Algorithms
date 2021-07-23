/**
 *  SCORE의 값을 최소화하라.
 *
 *  시간 제한 : 20초
 *
 *  main.cpp는 수정할 수 없다.
 *  user.cpp에 전역변수, static 변수 사용 불가
 *  user.cpp에 동적할당 사용 금지
 *  user.cpp에 대한 코드리뷰를 철저하게 진행할 것입니다.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "user.cpp"

// extern void test(unsigned char* FREQ, const unsigned char* BITMAP);
// extern void comp(unsigned char* COMP, const unsigned char* FREQ);
// extern void decomp(unsigned char* FREQ, const unsigned char* COMP);

unsigned long long _random() {
    static unsigned long long seed = 70ULL;
    return seed = (seed * 5832923371383ULL + 11ULL);
}

void clear(unsigned char* FREQ) {
    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 1000; x++) {
            FREQ[y * 1000 + x] = 0;
        }
    }
}

void add(unsigned char* FREQ, int y, int x) {
    if (!(0 <= y && y <= 5999)) return;
    if (!(0 <= x && x <= 5999)) return;

    x = x / 6;
    y = y / 6 * 1000;
    FREQ[x + y]++;
}

int sample(const unsigned char* BITMAP, int y, int x) {
    if (!(0 <= y && y <= 5999)) return -1;
    if (!(0 <= x && x <= 5999)) return -1;

    unsigned char mask = 0x80 >> (x % 8);
    x = x / 8;
    y = y * (6000 / 8);
    
    if ((BITMAP[x + y] & mask) == mask)
        return 1;
    else
        return 0;
}

void fill(unsigned char* FREQ, const unsigned char* BITMAP) {
    for (int y = 0; y < 6000; y++) 
        for (int x = 0; x < 6000; x++) 
            if (sample(BITMAP, y, x) == 1) 
                add(FREQ, y, x);
}

void process1(unsigned char* FREQ) {
    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 500; x++) {
            unsigned char temp = FREQ[y * 1000 + x];
            FREQ[y * 1000 + x] = FREQ[y * 1000 + (999 - x)];
            FREQ[y * 1000 + (999 - x)] = temp;
        }
    }
}

void process2(unsigned char* FREQ) {
    for (int y = 0; y < 500; y++) {
        for (int x = 0; x < 1000; x++) {
            unsigned char temp = FREQ[y * 1000 + x];
            FREQ[y * 1000 + x] = FREQ[(999 - y) * 1000 + x];
            FREQ[(999 - y) * 1000 + x] = temp;
        }
    }
}

void process3(unsigned char* FREQ) {
    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 1000; x++) {
            FREQ[y * 1000 + x] += 'J';
        }
    }
}

void build(unsigned char* FREQ, unsigned char* BITMAP) {
    clear(FREQ);
    fill(FREQ, BITMAP);
    process1(FREQ);
    process2(FREQ);
    process3(FREQ);
}

int main(int argc, char *argv[]) {
    static unsigned char BITMAP[4500000];
    static unsigned char DUMMY1[1240];
    static unsigned char FREQ1[1000000];
    static unsigned char DUMMY2[1022];
    static unsigned char FREQ2[1000000];
    static unsigned char DUMMY3[1122];
    static unsigned char FREQ3[1000000];
    static unsigned char DUMMY4[1015];
    static unsigned char COMP1[700000];
    static unsigned char DUMMY5[1209];
    static unsigned char COMP2[700000];

    int TC = 10;
    double SCORE = 30000000 * TC;

    for (int test_case = 1; test_case <= TC; test_case++) {
        for (int i = 0; i < 4500000; i++) {
            BITMAP[i] = _random();
        }

        build(FREQ1, BITMAP);

        time_t start = clock();
        test(FREQ2, BITMAP);
        comp(COMP1, FREQ2);
        memcpy(COMP2, COMP1, 700000);
        decomp(FREQ3, COMP2);
        for(int i = 0; i < 1000000; ++i){
            if(FREQ1[i] != FREQ2[i]){
                int here=1;
            }
            if(FREQ1[i] != FREQ3[i]){
                int here=1;
            }
        }
        SCORE += 1.0*(clock() - start) / 1000.0;

        if (memcmp(FREQ1, FREQ2, 1000000) == 0) SCORE -= 20000000;
        if (memcmp(FREQ1, FREQ3, 1000000) == 0) SCORE -= 10000000;
    }

    printf("%lf\n", SCORE);
    return 0;
}