#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"MemoryAllocUser.cpp"
#include<memory.h>

char memory[400000000];
char atbl[100000000];
extern void init_alloc(char memry[400000000], char atbl[100000000]);
extern char* alloc_mem(char atbl[100000000], int size);
extern void free_mem(char atbl[100000000], char* ptr); 
const int data_size[4] = {4,16,64,256};
int data_cnt[4] = {1,1,1,1};
char* user_func[4][100000000];

bool verify(){
    char table[256][256];
    for(int i = 0; i < 256; ++i){
        for(int j = 0;j < 256; ++j) table[i][j] = i;
    }

    int alloc_num = 0;
    for(int i = 0; i < 4; ++i){
        int c = data_cnt[i];
        for(int j = 0; j < c; ++j){
            if(user_func[i][j]) memset(user_func[i][j], j%256,data_size[i]);
        }
    }

    long long data2 = (long long) memory;
    for(int i = 0; i < 4; ++i){
        int c = data_cnt[i];
        for(int j = 0; j < c; ++j){
            long long data1 = (long long)user_func[i][j];
            if(user_func[i][j]){
                if(user_func[i][j] < memory || memory + 400000000 <= user_func[i][j]) 
                    return false;
                if(memcmp(user_func[i][j], table[j%256], data_size[i])) 
                    return false;
                alloc_num++;
            }
        }
    }
    if(!alloc_num) return false;
    return true;
}

int main(){
    int allocnum = 0, plus = 0;
    srand(1191);
    clock_t st = clock(), ed;
    init_alloc(memory, atbl);

    while(allocnum != 400000000){
        int uint = rand()%4;
        char* ptr = alloc_mem(atbl, data_size[uint]);
        long long lptr = (long long)ptr;
        if(ptr){
            allocnum+= data_size[uint];
            plus += data_size[uint];
        }
        else
        {
            plus -= data_size[uint];
        }
        if(data_cnt[uint] <=0) break;
        user_func[uint][data_cnt[uint]++] = ptr;
        uint = rand()%4;
        int c = rand()%data_cnt[uint];
        
        if(user_func[uint][c]){
            free_mem(atbl, user_func[uint][c]);
            user_func[uint][c] = 0;
            allocnum -= data_size[uint];
        }
    }
    int score = -10000000;
    ed = clock();
    if(verify()){
        score = (plus - (st-ed)/1000.0)/10000.0; 
    }
    printf("%d\n",score);
    return 0;
}