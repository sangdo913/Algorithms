#define MEM (0)
#define ST_P (MEM + sizeof(char*))
#define ST_CUR (ST_P + sizeof(int)*4)
#define ST_END (ST_CUR + sizeof(char*)*4)
#define ST (ST_END + sizeof(char*)*4)
#define ST4_SIZE 1176472
#define ST16_SIZE 1176470
#define ST64_SIZE 1176469
#define ST256_SIZE 1176471
#define STSIZE 2000000

void init_memory(char atbl[100000000], char memory[400000000]){
    char* mem = memory;
    char **st_pointer = (char**)&atbl[ST_CUR];
    st_pointer[0] = memory;
    st_pointer[1] = st_pointer[0] + ST4_SIZE*4;
    st_pointer[2] = st_pointer[1] + ST16_SIZE*16;
    st_pointer[3] = st_pointer[2] + ST64_SIZE*64;
    char **st_end = (char**)&atbl[ST_END];
    st_end[0] = st_pointer[1];
    st_end[1] = st_pointer[2];
    st_end[2] = st_pointer[3];
    st_end[3] = mem + 400000000;
}

char* alloc_memory(char atbl[100000000], int size){
    int idx;
    const int msize[4] = {4,16,64,256};
    char* ret = 0;
    if(size < 64){
        if(size == 4) idx = 0;
        else idx = 1;
    }
    else{
        if(size == 64) idx = 2;
        else idx = 3;
    }
    int *st_pointer = (int*)(atbl+ST_P);  
    char *st_end = ((char**)(atbl + ST_END))[idx];
    char **stcur = (char**)(atbl + ST_CUR);
    char* (*st)[2000000] = (char*(*)[2000000])(atbl + ST);
   
    if(st_pointer[idx]) {
        ret = st[idx][--st_pointer[idx]];
    }
    else if(st_end == stcur[idx]) {
        return 0;
    }
    else {
        ret = stcur[idx];
        stcur[idx] += msize[idx];
    }
    return ret;
}

void free_memory(char atbl[100000000], char* ptr) {
    char * mem = *(char**)atbl;
    char ** st_cur = (char**)(atbl + ST_CUR);
    int idx;
    if(ptr < st_cur[1]){
        if(ptr < st_cur[0]) idx = 0;
        else idx = 1;
    }
    else{
        if(ptr < st_cur[2]) idx = 2;
        else idx = 3;
    }
    char* (*st)[STSIZE] = (char*(*)[STSIZE])(atbl + ST);
    int *st_p = (int*)(atbl + ST_P);
    st[idx][st_p[idx]++] = ptr;
    return;
}