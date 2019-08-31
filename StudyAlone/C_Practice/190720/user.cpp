#define DES4  1176472
#define DES16 1176474
#define DES64 1176472
#define DES256 1176470
#define STSIZE 2000000
#define ST 0
#define STPTR (ST + 32*STSIZE)
#define CONV (STPTR + 4*4)
#define DES (CONV+257*4)
#define ALLOCNUM (DES + 4*4)
#define IDXSTART (ALLOCNUM + 4*4)
#define LOG (IDXSTART + 8*4)

void init_memory(char atbl[100000000], char memory[400000000]){
    int* des = (int*)(atbl + DES);
    des[0] = DES4;
    des[1] = DES16;
    des[2] = DES64;
    des[3] = DES256;

    int* conv = (int*)(atbl + CONV);
    conv[4] = 0, conv[16] = 1, conv[64] = 2, conv[256] = 3;

    char** idxsize = (char**)(atbl+IDXSTART);
    char** log = (char**)(atbl + LOG);
    log[0] = idxsize[0] = memory;
    log[1] = idxsize[1] = idxsize[0] + DES4*4;
    log[2] = idxsize[2] = idxsize[1] + DES16*16;
    log[3] = idxsize[3] = idxsize[2] + DES64*64;
}

char* alloc_memory(char atbl[100000000], int size){
    int idx = *(int*)(atbl + CONV + 4*size);
    char*(*stack)[STSIZE] = (char*(*)[STSIZE]) atbl;
    int* stsz = (int*)(atbl + STPTR + 4*idx);
    char* res = 0;
    int* des = (int*)(atbl + DES);
    int* allocnum = (int*)(atbl + ALLOCNUM);

    if(allocnum[idx] == des[idx]) {
        if(*stsz){
            return stack[idx][--(*stsz)];
        }
        return 0;
    }

    allocnum[idx]++;
    res = ((char**)(atbl+LOG))[idx];
    ((char**)(atbl+LOG))[idx] += size;

    return res;
}

void free_memory(char atbl[100000000], char* ptr){
    char** idxes = (char**)(atbl + IDXSTART);
    int idx;

    if(ptr < idxes[2]){
        idx = ptr < idxes[1] ? 0 : 1;
    }
    else{
        idx = ptr < idxes[3] ? 2 : 3;
    }

    int* stsz = (int*)(atbl + STPTR + 4 *idx);

    char*(*stack)[STSIZE] = (char*(*)[STSIZE]) atbl;
    stack[idx][(*stsz)++] = ptr;
}