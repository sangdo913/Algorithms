#define COUNT_4 3000000//1176472
#define COUNT_16 3000000//1176470
#define COUNT_64 3000000//1176473
#define COUNT_256 3000000//1176470
#define SP4 0
#define SP16 (COUNT_4*8)
#define SP64 (SP16 + 8*COUNT_16)
#define SP256 (SP64 + 8*COUNT_64)
#define STPTR4 (SP256+8*COUNT_256)
#define STPTR16 (STPTR4+4)
#define STPTR64 (STPTR16+4)
#define STPTR256 (STPTR64+4)
#define MEMSIZE (STPTR256+8)
#define LASTPTR (MEMSIZE + 8)
#define CNT (LASTPTR + 80)

#include<cstdio>
#include<iostream>

using namespace std;

void toInt(char* ptr, int num){
    for(int i = 0; i < 4; ++i){
        *(ptr+i) |= ((num>>(i*8)) & 0xff);
    }
}

int getInt(char* ptr){
    int res = 0;
    for(int i = 0; i < 4; ++i){
        res |= (1*((unsigned char)(*(ptr+i)))) << (i*8);
    }
    return res;
}

void toll(char* ptr, long long num){
    for(int i = 0; i< 8; ++i){
        *(ptr+i) |= ((num>>(i*8)) & 0xff);
    }
}

long long getll(char*ptr){
    long long ret = 0;
    for(int i = 0; i < 8; ++i){
        ret |= (1LL*((unsigned char)*(ptr+i)))<<(i*8); 
    }
    return ret;
}

void init_alloc(char memory[400000000], char atbl[100000000]){
    long long *memptr = (long long*)(&atbl[MEMSIZE]);
    long long *lastptr = (long long*)(atbl + LASTPTR);
    *memptr = (long long)memory;
    *lastptr = (long long)memory;
    printf("lld : %lld\n", (long long)STPTR256);
}

char* alloc_mem(char atbl[100000000], int size){
    long long* st;
    int* sp;
    int idx = 0;

    if(size == 4){
        st = (long long*)(atbl + SP4);
        sp = (int*)( atbl + STPTR4);
        idx = 0;
    }
    else if(size == 16){
        st = (long long*)(atbl + SP16);
        sp = (int*)(atbl + STPTR16);
        idx = 1;
    }
    else if(size == 64){
        st = (long long*)(atbl + SP64);
        sp = (int*)(atbl + STPTR64);
        idx = 2;
    }
    else{
        st = (long long*)(atbl + SP256);
        sp = (int*)(atbl + STPTR256);
        idx = 3;
    }
    long long* mem = (long long*)&atbl[CNT];
    if(*mem + size > 400000000) 
        return 0;

    *mem += size;

    if(*sp){
        return (char*)(st[--(*sp)]);
    }
    char* ret;
    long long lastptr = *(long long*)(&atbl[LASTPTR]);
    ret = (char*) lastptr; 
    *(char*)lastptr = (char)idx;
    *(long long*)(&atbl[LASTPTR]) += size;

    return ret;
}

void free_mem(char atbl[100000000], char* ptr) {
    long long mem = (*(long long*)&atbl[MEMSIZE]);
    long long lptr = (long long)ptr;
        if((long long)ptr < (long long) mem || (long long) ptr >= (mem + 400000000LL))
        int x = 1;
    long long offset[4] = {SP4, SP16, SP64, SP256};
    long long spoffset[4] = {STPTR4,STPTR16,STPTR64, STPTR256};
    int conv[4] = {4,16,64,256};
    long long check1 = (long long) ptr;
    char i = *ptr;
    // if((long long)ptr < (long long) mem || (long long) ptr >= (mem + 400000000LL))
    //     int x = 1;
    long long *st = (long long*)(&atbl[offset[i]]);
    int* sp = (int*)(&atbl[spoffset[i]]);
    st[(*sp)++] = (long long)ptr;
    (*(int*)&atbl[CNT]) -= conv[i];
}