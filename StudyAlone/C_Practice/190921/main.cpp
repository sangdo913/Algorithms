#include<cstdio>
#include<cstdlib>
#include<ctime>
//#include"user.cpp"

/*
문제

카드에 '1'~'5'까지의 숫자가 2개 써있는 카드 25개가 있다.
카드에 적힌 숫자는 10진수로 이어서 읽었을 때 모두 다르다.

이제 A와 B가 25장의 카드 중에서 5장씩 뽑는다.(뽑히는 카드는 모두 다른 카드)

이 카드로 둘이 승부를 한다.

처음에는 카드 5장의 10의 자리 숫자로 승부를 한다.
써있는 숫자에 따라 카드는 아래에 있는 규칙에 따라 '순위'를 가진다.
카드 숫자의 순위가 다르다면, 순위가 낮은 쪽이 게임에서 이기게 된다.

만약, 둘이 무승부가 난다면 1의 자리 숫자로 다시 한 번 승부를 한다. 
1의 자리 수에서도 무승부가 난다면, 해당 게임은 '무승부'이다.

단, 만약 10의 자리로 승부했을 때와 1의 자리로 승부했을 때 모두 5순위라면, 
10의 자리가 큰 수 부터 카드를 정렬 했을 때, 카드를 순서대로 보면서 1의 자리를 비교해서 더 큰 숫자가 승리한다.

카드의 순위는 아래와 같다.

규 to the 칙 
1 순위 : 5장 중 4장 같음
2 순위 : 5장 중 3장 같음
3 순위 : 5장 중 2장 같음 + 나머지 3장 중에서 2장이 같음
4 순위 : 5장 중 2장 같음
5 순위 : 다 다름
6 순위 : 다 같음

자, 그럼 순위가 같을 때 승부의 결과를 알아보자.
1 순위 : 나머지 카드 1장의 숫자가 큰 사람이 승리
2 순위 : 나머지 카드 2장의 숫자를 큰 숫자부터 봤을 때 큰 숫자를 가진 사람이 승리
3 순위, 4 순위 : 5장의 카드를 큰 순서 부터 봤을 때 큰 숫자를 가진 사람이 승리
(만약, 1~4순위에서 보고있는 카드가 모두 같다면 무승부로 처리한다.)
5 순위, 6 순위 : 그냥 무승부


A와 B가 카드를 5장씩 받는 100만개의 경우가 주어질 때,
A와 B의 승리를 결정지을 수 있는 경우의 수는 몇 개인지 출력하라.

또한, 최대한 SCORE가 작은 코드를 작성하라.
*/

const char * const card[25]= {
    "11","12","13", "14","15",
    "21","22","23","24","25",
    "31","32","33","34","35",
    "41","42","43","44","45",
    "51", "52", "53", "54", "55"
};

const char * A[1000000][5], *B[1000000][5];
extern int test(const char *A[1000000][5], const char *B[1000000][5]);

int main(){
    srand(5);

    int cardidx[25];
    clock_t st, ti = 0;
    for(int i = 0; i < 25; ++i) cardidx[i] = i;
    for(int tc = 1; tc <= 10; ++ tc){
        for(int i = 0; i < 1000000; ++i){
            int cnt = 10;
            while(cnt--){
                int a = rand()%25;
                int b = rand()%25;

                int temp;
                temp = cardidx[a];
                cardidx[a] = cardidx[b];
                cardidx[b] = temp;
            }
            
            for(int j = 0; j < 5; ++j){
                A[i][j] = card[cardidx[j]];    
                B[i][j] = card[cardidx[j+5]];
            }
        }
        st = clock();
        int res = test(A,B);
        ti += clock()-st;

        printf("#%d %d\n", tc, res);
    }
    printf("SCORE : %d\n", ti);
}