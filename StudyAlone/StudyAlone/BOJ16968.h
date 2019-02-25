#include<iostream>
#include<cstring>

using namespace std;

char cnum[5];
char mynum[4];
int num, sz;

void dfs(int len){
    if(len == sz){
        num++;
        return;
    }

    if(cnum[len] == 'd'){
        for(int i = '0'; i <= '9'; i++){
            if(len == 0 || mynum[len-1] != i){
                mynum[len] = i; dfs(len+1);
            }
        }
    }
    else{
        for(int i = 'a';  i<= 'z'; i++){
            if(len ==0 ||  mynum[len-1] != i){
                mynum[len] = i; dfs(len+1);
            }
        }
    }
}

int Do(){
    cin >> cnum;
    sz = strlen(cnum);
    dfs(0);
    cout << num++;
    return 0;
}