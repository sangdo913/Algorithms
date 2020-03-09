#include<iostream>
#include<cstring>
#define MAXNUM 10000000

using namespace std;
bool notprime[MAXNUM + 1];
int minfactor[MAXNUM+1];
int factorpower[MAXNUM+1];
int factornum[MAXNUM+1];
int main(){
    freopen("0Text.txt", "r" ,stdin);
    int C;
    cin >> C;
    factorpower[1] = 1;
    factorpower[2] = 1;
    factornum[1] = 1;
    
    for(int i = 0; i <= 10000000; ++i) minfactor[i] = i;
    for(int i = 2; i*i <= 10000000; i++){
        if(notprime[i] == true) continue;
        for(int j = i*i; j <= 10000000; j+=i){
            int n = j /i;
            notprime[j] = true;
            if(minfactor[j] == j) minfactor[j] = i;
        }
    }
    factorpower[1] = factornum[1] = 1;

    for(int i = 2; i <= MAXNUM; ++i){
        if(minfactor[i] == i){
            factorpower[i] = 2;
            factornum[i] = 1;
        }
        else{
            int m = minfactor[i];
            int n = i / m;
            if(n % m){
                factorpower[i] = 1;
            }
            else{
                factorpower[i] = factorpower[n] + 1;
            }
            factornum[i] = factornum[n] / factorpower[i] * (factorpower[i] + 1);
        }
    }

    while(C--){
        int n, lo, hi;
        cin >> n >> lo >> hi;
        int cnt = 0;
        for(int i = lo; i <= hi; ++i){
            cnt += factornum[i] == n;
        }
        cout << cnt << '\n';
    }

    return 0;
}