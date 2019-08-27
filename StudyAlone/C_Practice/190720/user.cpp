#define DES4  1176472
#define DES16 1176474
#define DES64 1176472
#define DES256 1176470
#define STSIZE 2000000
#define ST4 0
#define ST16 (ST4 + STSIZE*8)
#define ST64 (ST16 + STSIZE*8)
#define ST256 (ST64 + STSIZE*8)
#define ST4PTR (ST256 + STSIZE*8)
#define ST16PTR (ST4PTR + 4)
#define ST64PTR (ST16PTR + 4)
#define ST256PTR (ST64PTR + 4)
#define CONV (ST256PTR + 4)
#define MEMPTR (CONV + 300*4)
#define MEMBEG (MEMPTR + 8)
#define DES (MEMBEG+8)
#define ALLOCNUM (DES + 4*4)
#define LOGPTR (ALLOCNUM + 4*4)
#define LOG (LOGPTR + 8)

void init_memory(char atbl[100000000], char memory[400000000]){
    char** memptr = (char**)(atbl + MEMPTR);
    char** memnow = (char**)(atbl+ MEMBEG);

    *memptr = memory;
    *memnow = memory;

    int* des = (int*)(atbl + DES);

    des[0] = DES4;
    des[1] = DES16;
    des[2] = DES64;
    des[3] = DES256;

    int* conv = (int*)(atbl + CONV);
    conv[4] = 0, conv[16] = 1, conv[64] = 2, conv[256] = 3;
}

char* alloc_memory(char atbl[100000000], int size){
    int idx = *(int*)(atbl + CONV + 4*size);
    char*(*stack)[STSIZE] = (char*(*)[STSIZE]) atbl;
    int* stsz = (int*)(atbl + ST4PTR + 4*idx);
    char* res = 0;
    int* des = (int*)(atbl + DES);
    int* allocnum = (int*)(atbl + ALLOCNUM);
    char** memory = (char**)(atbl + MEMPTR);
    char** membeg = (char**)(atbl + MEMBEG);

    if(allocnum[idx] == des[idx]) return 0;
    allocnum[idx]++;

    if(*stsz){
        res = stack[idx][--(*stsz)];
    }
    else{
        int* logptr = (int*)(atbl + LOGPTR);
        ((int*)(atbl+LOG))[(*logptr)++] = size;
        res = *memory;
        *memory += size;
    }

    return res;
}

void free_memory(char atbl[100000000], char* ptr){
    char * memory = *(char**)(atbl + MEMBEG);
    int idx = 0;

    while(memory != ptr){
        memory += ((int*)(atbl + LOG))[idx++];
    }
    idx = ((int*)(atbl + CONV))[((int*)(atbl+LOG))[idx]];

    int* stsz = (int*)(atbl + ST4PTR + 4 *idx);
    int * allocnum = (int*)(atbl + ALLOCNUM);
    allocnum[idx]--;

    char*(*stack)[STSIZE] = (char*(*)[STSIZE]) atbl;
    stack[idx][(*stsz)++] = ptr;
}
