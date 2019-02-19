#include<iostream>
#include<cstdio>

using namespace std;

bool check[1000];
int MAX = 1, len;
char in[1001];
int dp[1001];

#define MAX(x, y) (((x) > (y)) ? (x) : (y) )

int dfs(int idx){
    int &ret = dp[idx];
    if(ret) return ret;
    dp[idx] = 1;

    for(int i = 1; idx + i  < len; i+=2){
        if(in[idx] == in[idx+i]){
            int temp = dfs(idx + i) + 1;
            ret = MAX(ret,temp);
        }
    }
        
    return ret;
}
int Do(){
    cin >> in;

    len =strlen(in);

    
    int res = 0;
    for(int i = 0; i < 1000; i++){
        res = MAX(dfs(i), res);
    }
    cout << res;
    return 0;
}