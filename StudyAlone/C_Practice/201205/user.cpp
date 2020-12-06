void culture(int n, int a, int b);
int covid_check(int n);
void clear(int n);
int f;
#define GROUP 5000

int mfind(int *count, int s, int e, bool need){
    if(s > e-1) return 0;
    if(s == e-1){
        if(!need || covid_check(s)) {
            clear(s);
            return 1;
        }
        return 0;
    }
    if(need) {
        (*count)++;
        for(int i = s; i < e; ++i){
            culture(*count,*count, i);
        }
        if(!covid_check(*count)) return 0;
    }

    int m = (s+e)/2;
    int ret = 0;
    bool find = false;
    (*count)++;
    int res = mfind(count, s,m,true);
    ret += res;
    ret += mfind(count, m, e,!!res);
    return ret;
}

void test(){
    int count = MAX_SIZE;
    int size;
    int remain = MAX_SIZE/1000;
    int l = 0, r = MAX_SIZE;
    while(r-l > remain){
        size = (r-l)/remain;
        int s = l;
        int e = s+size > MAX_SIZE ? MAX_SIZE : s+size;
        // printf("%d %d remain: %d size: %d\n", l,r, remain,size);
        int prev = SCORE;
        remain -= mfind(&count, s,e,true);
        printf("%d \n", SCORE-prev);
        l= e;
    }
    
    return ;
}