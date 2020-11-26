#define rint register int
#define RB 18
#define BM 0xfff
#define RB2 6
#define LB 12

int radix[(1<<LB)+1];
int temp[5000000];

long long solve(int* arr, int n){
    rint l = 1<<LB;
    register long long res = 0;
    for(rint i = 0; i < l; ++i) radix[i] = 0;
    for(rint i = 0;i < n; ++i) {
        radix[arr[i] >> RB]++;
    }
    for(rint i =1; i < l; ++i) radix[i] += radix[i-1];

    for(rint i = 0; i < n; ++i){
        int idx = arr[i] >>RB;
        temp[--radix[arr[i]>>RB]] =arr[i];
    }
    for(rint i = 0; i < n; ++i){
        arr[i] =temp[i];
    }
    l = 1<<LB;
    for(rint i = 0; i < n; ++i) {
        for(rint i= 0; i < l; ++i) radix[i] = 0;
        rint s = i;
        rint prev = arr[i] >>RB;
        while(i < n && (arr[i] >> RB) == prev){
            ++i;
        }
        for(rint j = s; j < i; ++j) radix[(arr[j] >> RB2)&BM]++;
        for(rint i = 1; i < l; ++i) radix[i] += radix[i-1];
        for(rint j = s; j < i; ++j) temp[--radix[(arr[j]>>RB2)&BM] + s] = arr[j];
        --i;
    }
    for(rint i = 0; i < n; ++i) arr[i] = temp[i];

    for(rint i = 0; i < n; ++i){
        rint s = i;
        rint j = i;
        rint v = arr[i];
        while(j && arr[j-1] > v){
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = v;
    }
    for(rint i = 1; i < n; i+=2) {
        res += arr[i];
    }

    return res;
}