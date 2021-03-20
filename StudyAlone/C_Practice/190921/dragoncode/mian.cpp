#include"user.cpp"



// 우선순위 1 : 같은 카드가 4장
// 우선순위 2 : 같은 카드가 3장
// 우선순위 3 : 같은 카드가 2장 x2
// 우선순위 4 : 같은 카드가 2장
// 우선순위 5 : 모두 다른카드
// 우선순위 6 : 모두 같은카드.

// 우선순위가 높은 카드가 승리.
// 우선순위가 같은 경우.
// 1 : 남은 카드 1장이 큰게 승리
// 2 : 남은 카드 중 큰 것들이 승리, 둘다 같으면 무승부
// 3, 4 : 카드를 큰 것부터 비교해서 큰 수가 승리.
// 5 : 무승부
// 6 : 무승부

// 10의 자리부터 비교.
// 10의 자리가 무승부면, 1의 자리 비교

// 10의 자리가 우선순위 5로 무승부고, 1의 자리가 우선순위 5로 무승부인 경우,
// 10의 자리가 큰 순서대로 정렬한 후, 비교해서 큰 쪽이 승리.

#include <stdio.h>
#include <time.h>
static int long seed = 5;

char* A[1000000][5];
char* B[1000000][5];
extern int test(char *A[1000000][5], char *B[1000000][5]);

static int pseudo_rand(void) {
   seed = seed * 214013 + 2531011;
   return (seed >> 16) & 0x7FFF;
}

static const char* cards[25] = {
      "11","12","13","14","15",
      "21","22","23","24","25",
      "31","32","33","34","35",
      "41","42","43","44","45",
      "51","52","53","54","55",
};
char num[25];
int main() {
   int score = 0;
   for (int i = 0; i < 25; ++i) num[i] = i;
   for (int tc = 1; tc <= 10; ++tc) {
      for (int c = 0; c < 1000000; ++c) {
         for (int n = 0; n < 10; ++n) {
            int a = pseudo_rand() % 25;
            int b = pseudo_rand() % 25;

            int t = num[a];
            num[a] = num[b];
            num[b] = t;
         }
         for (int n = 0; n < 5; ++n) {
            A[c][n] = (char *)cards[num[n]];
            B[c][n] = (char *)cards[num[n + 5]];
         }
      }
      int start = clock();
      int res = test(A, B);
      score += clock() - start;
      printf("#%d %d\n", tc, res);
   }
   printf("SCORE : %d\n", score);
   return 0;
}