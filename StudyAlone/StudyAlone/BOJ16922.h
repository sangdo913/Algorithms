#include<iostream>
#include<set>

using namespace std;
set<int> se;

int Do(){
    int n;
    long long res = 0;
    cin >> n;

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n-i; j++){
            for(int k = 0; k <= n-i-j; k++){
                int l = n-i-j-k;
                se.insert(i + 5*j + 10*k + 50*l);
            }
        }
    }
    cout << se.size();
    return 0;
}


int dp[13] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};
int Do2(){
    int n;
    cin >> n;
    
    return !(cout << (n < 13 ? dp[n] : 341 + (n - 12)*49));
}