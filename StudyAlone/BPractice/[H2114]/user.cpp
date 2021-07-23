
//void mstrcpy(char dst[], const char src[]) {
//  int c = 0;
//  while ((dst[c] = src[c]) != 0) ++c;
//}

//int mstrcmp(const char str1[], const char str2[]) {
//  int c = 0;
//  while (str1[c] != 0 && str1[c] == str2[c]) ++c;
//  return str1[c] - str2[c];
//}

#define R 
#define HSIZE 1000007

unsigned long long name[50][2];
int *duration;
char(*price)[100];
int plen[50];
int tc;
int nid = 0;
int n ;

void init(int N, char mName[50][20], char mPrice[50][100], int mDuration[50])
{
    n=N;
    tc+= 50;
    nid = 0;
    duration = mDuration;
    price = mPrice;
    for(R int i = 0; i < N; ++i) {
        unsigned long long k[2] = {0,0};
        R int l = 0;
        while(mName[i][l]){
            k[0] = (k[0] << 5) + ((k[1]>>55) &0x1f);
            k[1] = (k[1] << 5) + (mName[i][l]- 'a'+1);
            ++l;
        }
        l = 0;
        while(price[i][l]) price[i][l]-='0', ++l;
        plen[i] = l;
        name[i][0] = k[0];
        name[i][1] = k[1];
        R int s = 0, e = plen[i]-1;
        while(s < e){
            R int t = price[i][s];
            price[i][s] = price[i][e];
            price[i][e] =t;
            s++; e--;
        }
    }
}

void priceChange(char mName[20], char mPrice[100])
{
    unsigned long long k[2] = {0,0};
    R int l = 0;
    while(mName[l]){
        k[0] = (k[0] << 5) + ((k[1]>>55) &0x1f);
        k[1] = (k[1] << 5) + (mName[l]- 'a'+1);
        ++l;
    }
    R int id = 0;
    for(; id < n; ++id){
        if(name[id][0] == k[0] && name[id][1] == k[1]) break;
    }
    l = 0;
    while(mPrice[l]){
        mPrice[l] -='0';
        price[id][l] = mPrice[l];
        ++l;
    }
    R int s = 0, e = l-1;
    while(s < e){
        R int t = price[id][s];
        price[id][s] = price[id][e];
        price[id][e] =t;
        s++; e--;
    }
    plen[id] = l;
}

int res[110];
char rlen;

int mul(char *a, int la, char *b, int lb){
    for(R int i = 0; i < 109; ++i) res[i] = 0;
    for(int i = 0; i < la; ++i) {
        for(int j = 0; j < lb; ++j) {
            res[i+j] += a[i] * b[j];
        }
    }
    R int l = la+lb;
    while(l && res[l] == 0) --l;
    return l+1;
}

int sumarr[110];
char sumlen = 0;

void sum(int *a, int la) {
    for(R int i = 0; i < la; ++i) {
        sumarr[i] += a[i];
    }
}

char oper[10];

int toChar(int v){
    int l = 0;
    while(v){
        oper[l++] = v%10;
        v/=10;
    }
    return l;
}
bool cmp(int *a ,char *b){
    R int l = 109;
    for(R int i = 0; i < l; ++i) {
        a[i+1] += a[i]/10;
        a[i] %=10;
    }
    l = 99;
    while(l && a[l] == b[l]) l--;
    return a[l] <= b[l];
}

int daySurvivable(char mMoney[100])
{
    R int s = 1, e = 3001;
    R int l = 0;
    while(mMoney[l]) mMoney[l++]-='0';
    for(R int i = 0; i < l/2; ++i){
        int t = mMoney[i];
        mMoney[i] = mMoney[l-1-i];
        mMoney[l-1-i] = t;
    }
    while(s < e) {
      for(R int i = 0; i < 110; ++i) sumarr[i] = 0;
      sumlen = 0;
      R int m = (s+e)/2;  
      for(R int i = 0; i < n; ++i) {
          R int need = (m/duration[i]) + (m%duration[i] != 0);
          int operLen = toChar(need);
          rlen = mul(price[i], plen[i], oper, operLen);
          sum(res, rlen);
      }
      if(cmp(sumarr, mMoney)){ s = m+1; }
      else e = m;
    }
    return e-1;
}