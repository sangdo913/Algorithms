#include<cstdio>

int encode(char *paper, char* src, int papern){
   int cur = 0; 
   char myhash[1024][8] = {};
   long long str[1024]= {};
   int table[20000];
   int len[1024] = {};
   int strlen = 0;
   int kcnt = 0;
   while(paper[cur]){
       long long h= 0;
       int l = 0;
       while(paper[cur] != ' ' && paper[cur]){
          h = (h<<5) + paper[cur]-'a'+1; 
          ++l;
          cur++;
       }
       int key = h%1024;
       while(len[key] && str[key] != h) key = (++key)%1024;
       if(len[key] == 0) {
           str[key] = h;
           len[key] = l;
           for(int i = 0; i < l; ++i) {
               myhash[key][i] = paper[cur-l+i];
           }
            // printf("%s %d %lld\n", myhash[key],kcnt++, str[key]);
       }
       table[strlen++] = key;

       if(paper[cur] == 0) break;
       cur++;
   }
   //hash table push
   int b = 0;
   int bcnt;
   int store;
   for(int i = 0; i < 1024; ++i) {
    //    printf("%s\n", myhash[i]);
       int l = store = len[i];
       bcnt = 3;
       while(bcnt--){
           src[(b+bcnt)/8] |= (store & 1) << ((b+bcnt)%8);
           store>>=1;
       }
       b+=3;
       for(int j = 0; j < l; ++j){
           bcnt = 5;
           int a = myhash[i][j]-'a';
           while(bcnt--){
               src[(b+bcnt)/8] |= (a&1) << ((b+bcnt)%8);
               a>>=1;
           }
           b+=5;
       }
   }
   bcnt = 15;
   store = strlen;
//    printf("%d\n", strlen);
   while(bcnt--){
       src[(b+bcnt)/8] |= (store&1) << ((b+bcnt)%8);
       store >>=1;
   }
   b+=15;
   for(int i = 0; i < strlen; ++i){
       bcnt = 10;
       int num = table[i];
       while(bcnt--) {
           src[(b+bcnt)/8] |= (num & 1) << ((b+bcnt)%8);
           num >>= 1;
       }
       b+=10;
   }
   return b/8+1;
}
void decode(char* src, char * dest, int s){
    int len[1024];
    char myhash[1024][8] = {};
    int tablelen = 0;
    int b=0, bcnt;

    for(int i = 0; i < 1024; ++i) {
        bcnt =3;
        int l = 0;
        while(bcnt--) {
            l = (l<<1) + (src[b/8] & 1);
            src[b/8] >>=1;
            b++;
        }
        len[i] = l;
        for(int j = 0; j < l; ++j) {
            bcnt = 5;
            char c = 0;
            while(bcnt--) {
                c = (c<<1) + (src[b/8] & 1);
                src[b/8] >>=1;
                b++;
            }
            myhash[i][j] = c+'a';
        }
    }
    int x =1;
    bcnt = 15;
    while(bcnt--){
        tablelen = (tablelen << 1) + (src[b/8] & 1);
        src[b/8] >>=1;
        ++b;
    }
    int cur = 0;
    for(int i = 0; i < tablelen; ++i){
        bcnt = 10;
        int k = 0;
        while(bcnt--){
            k = (k<<1) + (src[b/8] & 1);
            src[b/8] >>=1;
            ++b;
        }
        for(int i = 0; i < len[k]; ++i){
            dest[cur++] = myhash[k][i];
        }
        dest[cur++] = ' ';
    }
    dest[cur-1] = 0;
    for(int i = 0; i < s; ++i) src[i] = 0;
}