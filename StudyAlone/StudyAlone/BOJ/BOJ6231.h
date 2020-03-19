#include<iostream>
#define MOD 10007
#include<algorithm>

using namespace std;

int rangesum[100001][30];
int bits[MOD];

bool parametric(int n){

    return false;
}

int main(){
    freopen("0Text.txt","r", stdin);
    int n, k;
    cin >> n >> k;
    for(int i = 0 ; i < k; ++i) {
        bits[(1<<i)%MOD] = i;
    }

    for(int i = 1; i <= n; ++i){
        int num;
        cin >> num; 
        while(num){
            int b = num & -num;
            rangesum[i][bits[b%MOD]] = 1;
            num -= b;
        }
        for(int j = 0; j < k; ++j){
            rangesum[i][j] += rangesum[i-1][j];
        }
    }

    for(int i = 1; i <= n; ++i){
        int l , r;
        int min = 0x3f3f3f3f;
        for(int j = 0; j < k; ++j){
            int diff = rangesum[i-1][j] - rangesum[n][j];
            if(min > diff) min = diff;
        }
        l = 0, r = min;

        while(l <= r){
            int m = (l+r)/2;
            if(parametric(m)){
                m = l+1;
            }
            else m = r-1;
        }
    }

    return 0;
}