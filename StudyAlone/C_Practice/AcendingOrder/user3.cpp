#define rint register int
#define CSIZE 24

#define RSIZE 12
#define R2SIZE 12
#define R3SIZE 6

#define RL 18
#define R2L 6

#define R2B 0xfff
#define R3B 0x3f
int cnt[1<<CSIZE] = {};
int radix[2][5000000];

long long solve(int* arr, int n) {
    rint e;
    e = 1<<RSIZE;
    for(rint i = 0; i < e; ++i) cnt[i] = 0;
    for(rint i = 0; i < n; ++i) {
        rint g = arr[i] >>RL;
        cnt[g]++;
    }
    e = 1<<RSIZE;
    for(rint i = 1; i < e; ++i){
        cnt[i] += cnt[i-1];
    }
    for(rint i = 0; i < n; ++i) {
        radix[0][--cnt[arr[i]>>RL]] = arr[i];
    }
    rint l;
    for(rint i = 0; i < n;) { 
        l = i;
        rint g = radix[0][l] >> RL;
        while(i <n && (radix[0][i] >> RL) == g) ++i;
        e = 1<<R2SIZE;
        for(rint i = 1; i < e; ++i) cnt[i] = 0;
        cnt[0] = l;
        for(rint j = l; j < i; ++j){
            cnt[(radix[0][j] >> R2L) &R2B]++;
        }
        rint r = 1 << R2SIZE;
        for(rint i = 1; i < r; ++i) cnt[i] += cnt[i-1];
        for(rint j = l; j <i; ++j) {
            radix[1][--cnt[(radix[0][j] >> R2L) & R2B]] = radix[0][j];
        }
    }
    register long long res = 0;
    for(rint i = 0; i < n; ++i) {
        int j = i;
        int v = radix[1][j];
        while(j && v < radix[1][j-1]) {
            radix[1][j] = radix[1][j-1];
            --j;
        }
        radix[1][j] = v;
    }
    for(rint i = 1; i < n; i+=2) res += radix[1][i];
    
    return res;
}