#include<iostream>
#include<queue>

using namespace std;

int arr[10000];

int main(){
    typedef char(*A[100]);
    int cnt = 0;
    for(int i = 0; i < 10000; ++i){
        arr[i] = cnt++;
    }

    int (*b)[20][30] = (int(*)[20][30])&arr[1];
    for(int i = 0; i*30 < 100; i++){
        for(int j = 0; j < 30; j++){
            printf("%d ", b[0][i][j]);
        }
        printf("\n");
    }
    return 0;
}