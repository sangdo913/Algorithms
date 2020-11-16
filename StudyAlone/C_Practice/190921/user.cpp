int memoi[5][5][5][5][5];
int conv[256];
int plus[256];

#define memo(a,b) memoi[conv[a[0][b]]][conv[a[1][b]]][conv[a[2][b]]][conv[a[3][b]]][conv[a[4][b]]]

int getValue(int a[5]){
    int cnt[6] = {};
    int numcnt[6] = {};

    int maxv = 0;

    for(int i = 0; i < 5; ++i) ++cnt[a[i]];
    for(int i = 0; i < 5; ++i) maxv = maxv < cnt[i] ? cnt[i] : maxv, ++numcnt[cnt[i]];
    int ret = 0;
    
    switch(maxv){
        case 5: return 0;
        case 4:
            ret = 100000000;
            for(int i = 0; i < 5; ++i) {
                if(cnt[a[i]] == 1) ret += a[i];
            }
            return ret;
        case 3:
            ret = 200000000;
            for(int i = 0; i < 5; ++i){
                if(cnt[a[i]] != maxv) ret += cnt[a[i]]*plus[a[i]];
            }
            return ret;
        break;
        case 2:
            if(numcnt[2] == 2){
                ret = 300000000;
            }
            else{
                ret = 400000000;
            }
            for(int i = 0; i < 5; ++i) ret += cnt[a[i]]*plus[a[i]];
            return ret;
        case 1: return 1;
    }
}

int test( char *A[1000000][5],  char *B[1000000][5]){
    for(int i  = '1'; i <= '5'; ++i) conv[i] = i - '1';

    plus[0] = 1;
    for(int i = 1; i <= 4; ++i) plus[i] = plus[i-1] *5;
    for(int i = 0; i <= 4; ++i) for(int j = 0; j <= 4; ++j) for(int k = 0; k <=4 ; ++k) for(int l = 0; l <=4; ++l) for(int m = 0; m <=4; ++m) 
    {
        int arr[5] = {i,j,k,l,m}; 
        memoi[i][j][k][l][m] = getValue(arr);
    }
    int res = 1000000;

    for(int i = 0; i < 1000000; ++i){
        int a = memo(A[i], 0);
        int b = memo(B[i], 0);
        if(a != b) continue;
        int c = memo(A[i],1);
        int d = memo(B[i],1);

        if(c != d) continue;
        res--;

        if(c == 1&& a == 1){
            int sum1 = 0, sum2 =0;
            for(int j = 0; j < 5; ++j){
                sum1 += plus[conv[A[i][j][0]]]*conv[A[i][j][1]];
                sum2 += plus[conv[B[i][j][0]]]*conv[B[i][j][1]];
            }
            if(sum1 != sum2) {
                res++;
            }
        } 
    }
    return res;
}