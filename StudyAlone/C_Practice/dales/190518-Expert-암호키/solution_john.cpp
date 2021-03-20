/*
 * TODO:
 * 1) recursive 함수 inline으로 test() 안에 짜보기
 * -> PCK랑 차이가 그것뿐인거가은데.. 함수호출에서 오래걸리남
 *
 * 2) softech 보고 2개숫자 동시에 체크하기
 * -> 해적님 솔루션
 */

#define SIZE 200

extern int check(unsigned char *key);

unsigned char sol[SIZE];

int fillAndCheck(int from, int to, int val) {
    register int i;
    for (i = 0; i < from; ++i) {
        sol[i] = 0;
    }
    for (i = from; i <=  to; ++i) {
        sol[i] = val;
    }
    for (i = to + 1; i < SIZE ; ++i) {
        sol[i] = 0;
    }

    int ret = check(sol);
    return ret;
}
int findPosition(int from, int to, int val) {
    int mid = (from + to) / 2;
    int ret = fillAndCheck(from, mid, val);
    ret = ret / 256;

    // base case
    if(from == mid){
        if(ret) return from;
        return from + 1;
    }

    int pos;
    if(ret) {
         pos = findPosition(from, mid, val);
    }
    else {
        pos = findPosition(mid + 1, to, val);
    }
    return pos;
}
void test(unsigned char *key) {
    for (int j = 0; j < 200; ++j) {
        sol[j] = 0;
    }

    register int i = 0, count = 0;
    int s = 0, e = 199, m = 99;
    int ret, pos;
    while(i < 255 && count < 200) {
        i++;
        ret = fillAndCheck(s, m, i);

        // not exist anywhere
        if(ret % 256 == 0) continue;

        // exist in this side
        if(ret / 256 == 1) {
            pos = findPosition(s, m, i);
        }
        // exist in the another side
        else if(ret / 256 == 0) {
            pos = findPosition(m + 1, e, i);
        }
        count ++;
        key[pos] = i;
    }
}

