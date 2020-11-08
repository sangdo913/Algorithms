#define STSIZE (sizeof(void*)*3000000)
#define MEMROY_SIZE (400000000)
#define MEMORY_PTR (0)
#define MEMORY_CUR4 (MEMORY_PTR + sizeof(char*))
#define MEMORY_CUR16 (MEMORY_CUR4 + sizeof(char*))
#define MEMORY_CUR64 (MEMORY_CUR16 + sizeof(char*))
#define MEMORY_CUR256 (MEMORY_CUR64 + sizeof(char*))
#define ST4 (MEMORY_CUR256 + sizeof(char*))
#define ST16 (ST4 + sizeof(char*)*2000000)
#define ST64 (ST16 + sizeof(char*)*2000000)
#define ST256 (ST64 + sizeof(char*)*2000000)
#define ST4_SIZE 1176472
#define ST16_SIZE 1176470
#define ST64_SIZE 1176469
#define ST256_SIZE 1176471

void init_alloc(char memory[400000000], char atbl[100000000]){
    char* mem = atbl;
    mem = memory;
    int (*st_cur)[4] = (int(*)[4])&atbl[MEMORY_CUR4];
}

char* alloc_mem(char atbl[100000000], int size){
    char (*st)[STSIZE] = (char(*)[STSIZE])(&atbl[ST4_PTR]);
    return 0;
}
void free_mem(char atbl[100000000], char* ptr){

} 