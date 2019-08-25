#include <iostream>
#include <time.h>
#include <stdlib.h>

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

int p_rand() {
   return 0;
}

bool _verify() {

   char cmp[256][256];

   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < unit_count[i]; ++j) {
         if(unit_ptr[i][j] != NULL){
            memset(unit_ptr, j % mod, unit_size[i]);
         }
      }
   }
   for (int i = 0; i < 256; ++i) memset(cmp[i], i % mod, 256);

   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < unit_count[i]; ++j) {
         if (unit_ptr[i][j] != NULL) {
            memset(unit_ptr, j % mod, unit_size[i]);
            if (unit_ptr[i][j] < memory || unit_ptr[i][j] + unit_count[i]> memory + 400000000) return false;
            if (memcmp(cmp[i], unit_ptr, unit_size[i]) != 0) return false;
         }
      }
   }
   return true;

}

int main() {
   int alloc_total = 0;
   int unit_total = 0;

   clock_t start = clock();

   for (int c = 0; c < 4; ++c) {
      unit_count[c] = 1;
      unit_ptr[c][0] = NULL;
   }
   init_memory(atbl, memory);

   while (unit_total != 400000000) {
      int unit = p_rand() % 4;
      char* ptr = alloc_memory(atbl, unit_size[unit]);
      unit_count[unit]++;

      if (ptr != NULL) {
         unit_total += unit_size[unit];
         alloc_total += unit_size[unit];
         memset(ptr, 0, unit_size[unit]);
      }
      else alloc_total -= unit_size[unit];

      unit = p_rand() % 4;
      if (unit_count[unit] <= 0)
         break;

      int index = p_rand() % unit_count[unit];
      
      if (unit_ptr[unit][index] != 0) {
         free_memory(atbl, unit_ptr[unit][index]);
         unit_ptr[unit][index] = NULL;
         unit_total -= unit_size[unit];
      }
   }

   long long SCORE = alloc_total - ((clock() - start) / (CLOCKS_PER_SEC / 10000)) / 100000;
   if (_verify() == false) SCORE = 0;

   printf("%20.5lf\n", SCORE);

   return 0;
}