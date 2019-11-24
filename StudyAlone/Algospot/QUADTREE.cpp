#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>

using namespace std;
char str[1000];
char to[1000];
int i;

void merge(){
    if(str[i] != 'x'){
        to[i] = str[i];
        ++i;
        return;
    }
    int st = i;
    to[i++] = 'x';
    int a1 = i;
    merge();
    int a2 = i;
    merge();
    int a3 = i;
    merge();
    int a4 = i;
    merge();
    int a5 = i;
    int cnt[4] = {a4-a3, a5-a4, a2-a1, a3-a2};
    int idx = a1;
    for(int d = 0; d < cnt[0]; ++d){
        str[idx++] = to[a3+d];
    }
    for(int d=  0; d < cnt[1]; ++d) str[idx++] = to[a4+d];
    for(int d = 0; d < cnt[2]; ++d) str[idx++] = to[a1 + d];
    for(int d = 0; d < cnt[3]; ++d) str[idx++] = to[a2 + d];
    for(int i = st; i < a5; ++i) to[i] = str[i];
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--){
        i = 0;
        scanf("%s ", str);
        merge();
        printf("%s\n", str);
    }


    return 0;
}