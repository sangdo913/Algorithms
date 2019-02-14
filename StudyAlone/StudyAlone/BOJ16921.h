#include<iostream>

using namespace std;

int dp[13] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};
int Do(){
    int n;
    cin >> n;
    
    return !(cout << (n < 13 ? dp[n] : 341 + (n - 12)*49));
}