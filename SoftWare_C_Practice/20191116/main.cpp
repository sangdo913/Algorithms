#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"user.cpp"

char alpha[1111];
char dest[65536];
int dummy[10000];
char src[65536];
int dummy2[10000];
char paper[65536];
char dic[1024][7];
int ndic[1024];
const int cnt[26] = {7, 49, 73, 58, 30, 72, 44, 78, 23, 9, 40, 65, 92, 42, 87, 3, 27, 29, 40, 12, 3, 69, 9, 57, 60, 33};

extern int encode(char *paper, char* src, int papern);
extern void decode(char* src, char * dest, int s);

void init(){
    int idx = 0;
    for(int i = 0; i < 26; ++i){
        int c = cnt[i];
        while(c--) alpha[idx++] = 'a' + i;
    }
}

int build(){
     for(int i = 0; i < 1024; ++i){
        ndic[i] = rand()%7 + 1;
        for(int j = 0; j < ndic[i]; ++j) dic[i][j] = alpha[rand()%1111];
     }
     int len = 0;

     while(1){
         int id = rand()%1024;
         if(len + ndic[id] > 65535) break;
         for(int i = 0; i < ndic[id]; ++i){
            paper[len + i] = dic[id][i];
         }
         paper[len +ndic[id]] = ' ';
         len += ndic[id] + 1;
     }
     return len-1;
}

int main(){
    clock_t TIME = clock();
    srand(time(0));
    unsigned int RATE = 0;
    init();
    for(int c = 0; c < 100; ++c){
        bool isfail = false;
        for(int i = 0; i < 65536; ++i) dest[i] = 0;
        int len = build();
        paper[len] = 0;

        int s = encode(paper, src, len);
        for (int i = s; i < 65536; ++i) src[i] = 0;

        decode(src, dest, s);
        
        if(memcmp(dest, paper, len)){
            RATE += 100000;
            isfail = true;
        }
        else{
            RATE += s;
        }
        if(isfail) printf("FAIL\n");
    }

    TIME = clock() - TIME;
    printf("total score : %lf", TIME/1000.0 + RATE);

    return 0;
}
