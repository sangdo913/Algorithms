#include <iostream>
#include <random>
#include <algorithm>
#include "user2.cpp"
int SCORE = 0;
void culture(int n, int a, int b);
int covid_check(int n);
void clear(int n);
int tray[MAX_SIZE * 2];

using namespace std;
int gettray(int n){
   return tray[n];
}

extern void test();
int covid_check(int n) {
   SCORE += 1;
   if (n < 0 || n >= MAX_SIZE * 2) {
      return tray[0];
   }
   return tray[n];
}

void culture(int n, int a, int b) {
   if (n < MAX_SIZE || n >= MAX_SIZE * 2) return;
   tray[n] = tray[a] | tray[b];
}

void clear(int n) {
   SCORE += 10;
   if (n < 0 || n >= MAX_SIZE * 2) return;
   tray[n] = 0;
}

int main() {
   mt19937_64 mtRand;

   for (int i = 0; i < MAX_SIZE / 1000; ++i) tray[mtRand()*3 % MAX_SIZE] = 1;
   test();

   for (int i = 0; i < MAX_SIZE; ++i) {
      if(tray[i]){
         SCORE += tray[i] * 10000;
      }
   }

   cout << "SCORE : " << SCORE << endl;
}