#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<cstring>
#include"user2.cpp"
#include<cstdio>
using namespace std;


char memory[400000000];
char dummy[145124];
char atbl[100000000];

int mod = 256;
int unit_size[4] = { 4, 16, 64, 256 };

extern void init_memory(char atbl[100000000], char memory[400000000]);
extern char* alloc_memory(char atbl[100000000], int size);
extern void free_memory(char atbl[100000000], char* ptr);

char* unit_ptr[4][10000000];
int unit_count[4];

bool _verify() {
   char cmp[256][256];

   for (int i = 0; i < 256; ++i) memset(cmp[i], i, 256);
   for (int i = 0; i < 4; ++i){
      for(int j = 0; j < unit_count[i]; ++j){
         if(unit_ptr[i][j]){
            if (unit_ptr[i][j] < memory || unit_ptr[i][j] + unit_size[i]> memory + 400000000) 
               return false;
            memset(unit_ptr[i][j], j%mod, unit_size[i]);
         }
      }
   }

   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < unit_count[i]; ++j) {
         if (unit_ptr[i][j]) {
            int idx = *unit_ptr[i][j];
            if(idx < 0 ) idx +=256;
            if (memcmp(cmp[idx], unit_ptr[i][j], unit_size[i]) != 0) 
               return false;
         }
      }
   }
   return true;
}

int main() {
   long long alloc_total = 0;
   int unit_total = 0;

   clock_t start = clock();

   for (int c = 0; c < 4; ++c) {
      unit_count[c] = 1;
      unit_ptr[c][0] = NULL;
   }
   init_memory(atbl, memory);
   srand(time(0));
   int count = 0;
   int loop = 0;

   while (unit_total != 400000000) {
      loop++;
      // if(loop %1000000 == 0){
      //    //printf("alloc: %d\n", alloc_total);
      // }
      int unit = rand() % 4;
      char* ptr = alloc_memory(atbl, unit_size[unit]);

      if (ptr != NULL) {
         unit_total += unit_size[unit];
         alloc_total += unit_size[unit];
         memset(ptr, 0, unit_size[unit]);
         unit_ptr[unit][unit_count[unit]++] = ptr; //추가했음
      }

      else alloc_total -= unit_size[unit];

      unit = rand() % 4;
      if (unit_count[unit] <= 0)
         break;

      int index = rand()% unit_count[unit];

      if (unit_ptr[unit][index] != 0) {
         free_memory(atbl, unit_ptr[unit][index]);
         unit_ptr[unit][index] = NULL;
         unit_total -= unit_size[unit];
         count++;
      }
   }

   long long exectime = ((long long)clock()-start) / (CLOCKS_PER_SEC/1000);
   long long SCORE = alloc_total - exectime*100000LL;
   if (_verify() == false) 
       SCORE = 0;

   printf("score: %lld\n", SCORE);
   printf("time : %d\n", exectime);
   printf("loop : %d\ncount : %d\n",loop, count);
   

   return 0;
}