//Magnus
//https://www.acmicpc.net/problem/16755
#include<iostream>
#include<cstring>

using namespace std;

int dp[200000];
int MAX(int a, int b){return a < b ? b : a;}
int len;
char str[200000];

char flag[5] = "HONI";

int Do(){
    cin >> str;
    len = strlen(str);

    int res = 0;
    int now = 0;
    for(int i = 0; i < len; i++){
        if(str[i] == flag[now]){
            now++;
            if(now == 4){
                now = 0; res++;
            }
        }
    }
    cout << res;
    return 0;
}