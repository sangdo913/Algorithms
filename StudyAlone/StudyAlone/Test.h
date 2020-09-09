#include<stdio.h>

int main(){
    int n = 2003;
    int i = 1;
    for(i = 2; i*i <= n; ++i ){
        while(n% i == 0){
            n/=i;
            printf("%d ", i);
        }
    }
    return 0;
}