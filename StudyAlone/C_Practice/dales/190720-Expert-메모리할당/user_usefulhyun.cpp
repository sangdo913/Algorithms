//제가 푼 방식을 코드 일부분로 설명해볼게요.

#define MEMORY 0 // long long
#define STACK_4 8 // array of integers with size 10000
#define STACK_16 40008 // same with the above
 
 
#define STACK_POINTER 160008 // array of integers with size 4 
#define COUNTER 170000 // array of integers with size 4
 
 
#define MAX_COUNTER_4 1176472
#define MAX_COUNTER_16 1176470
#define MAX_COUNTER_64 1176473
#define MAX_COUNTER_256 1176470
 
 
#define OFFSET_4 0
#define OFFSET_16 (OFFSET_4 + (MAX_COUNTER_4*4) )
 
 
void init_block(char atbl[100000000], char memory[400000000])
{
 long long& mem_ptr = *((long long*)(&atbl[MEMORY]));
 mem_ptr = (long long)memory;
 
 
 int* stack_4 = (int *)(&atbl[STACK_4]);
 int* stack_16 = (int *)(&atbl[STACK_16]);
 int* stack_pointer = (int *)(&atbl[STACK_POINTER]);
 int* counter = (int *)(&atbl[COUNTER]);
 
 
 for (int i = 0; i < 4; i++) {
  stack_pointer[i] = 0;
  counter[i] = 0;
 }
}
 
 
char *alloc_block(char atbl[100000000], int size) {
 long long& mem_ptr = *((long long*)(&atbl[MEMORY]));
 char* memory = (char *)mem_ptr;
 
 
 int* stack_4 = (int *)(&atbl[STACK_4]);
 int* stack_16 = (int *)(&atbl[STACK_16]);
 int* stack_pointer = (int *)(&atbl[STACK_POINTER]);
 int* counter = (int *)(&atbl[COUNTER]);
 
 
 if (size == 4){
  if (stack_pointer[0] > 0)
   return &memory[stack_4[--stack_pointer[0]]];
  else if (counter[0] < MAX_COUNTER_4)
   return &memory[OFFSET_4 + (counter[0]++) * 4];
 }
 else if (size == 16) {
  if (stack_pointer[1] > 0)
   return &memory[stack_16[--stack_pointer[1]]];
  else if (counter[1] < MAX_COUNTER_16)
   return &memory[OFFSET_16 + (counter[1]++) * 16];
 }
 return 0; // 0 is NULL
}
 
 
void free_block(char atbl[100000000], char* ptr) {
 long long& mem_ptr = *((long long*)(&atbl[MEMORY]));
 char* memory = (char *)mem_ptr;
 
 
 int* stack_4 = (int *)(&atbl[STACK_4]);
 int* stack_16 = (int *)(&atbl[STACK_16]);
 int* stack_pointer = (int *)(&atbl[STACK_POINTER]);
 
 
 int index = ptr - memory;
 if (OFFSET_4 <= index && index < OFFSET_16) // size is 4
  stack_4[stack_pointer[0]++] = index;
 else if (OFFSET_16 <= index && index < OFFSET_64) // size is 16
  stack_16[stack_pointer[1]++] = index;
}
