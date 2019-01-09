//Á¦°ö¼öÀÇ ÇÕ
//https://www.acmicpc.net/problem/1699
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int dp[100001];
int nums[10000];

int MIN(int a, int b){return a< b ? a : b;}

int Do(){
    int n;
    cin >> n;
    int idx = 0;

    memset(dp, 0x3f, sizeof(dp));

    dp[0] = 0;

    for(int i = 1; i*i <= n; i++){
        nums[idx++] = i*i;
    }

    for(int num = 1; num <= n; num++){
        for(int j = 0; j < idx; j++){
            if(num < nums[j]) break;
            dp[num] = MIN(dp[num], dp[num-nums[j]] + 1);
        }
    }
    cout << dp[n];
    return 0;
}