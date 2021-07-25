#include<iostream>
#include<ctime>
#include"user.cpp"
using namespace std;

static unsigned int mrand()
{
   static unsigned int seed = 3;
   return (unsigned int) (seed = seed * 25214903917ULL + 11ULL);
}

//can be changed
int build(int num) {
    int res = 0;
    int i = 0;
    for(i = 1; i*i < num; ++i) {
        if(num%i ==0) res+=2;
    }
    res += i*i == num;
    return res;
}
char function_code[10000];

int main() {
    int cnt = 10;
    int tc = 1000;
    int result = 0;
    int res = 0;
    double t = 0;
    clock_t st = clock();
    code(function_code);

    for(int j = 0; j < tc ;++j) {

        int num = mrand()%1000000001 + 1000000000;
        int user_result = run(num, function_code);
        int result = build(num);
        if(user_result != result) t += 10000;
    }
    clock_t ed = clock();
    cout << t+1.0*(ed-st)/CLOCKS_PER_SEC*1000.0 << endl;
}
/*
#include <stdio.h>
#include "user.cpp"
#include <time.h>

static unsigned int random()
{
   static unsigned int seed = 3;
   return (unsigned int) (seed = seed * 25214903917ULL + 11ULL);
}

char str[10000];

int main()
{
   code(str);

   clock_t start = clock();

   int RESULT = 0;
   for (int tc = 0; tc < 1000; ++tc) {
      int num = random() % 1000000001 + 1000000000;
      RESULT += run(num, str);
   }

   printf("%d\n", RESULT);
   if (RESULT != 24556)
      RESULT = 1000000;
   else
      RESULT = 0;

   RESULT += (clock() - start) / (CLOCKS_PER_SEC / 1000);

   printf("RESULT : %d\n", RESULT);
}
*/