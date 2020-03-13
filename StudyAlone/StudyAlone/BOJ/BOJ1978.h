#include<iostream>

using namespace std;
int noprime[1001];

int main(){
    freopen("0Text.txt", "r" ,stdin);
    int n;
    cin >> n;

    noprime[1] = true;
    for(int i = 2; i*i <= 1000; ++i){
        if(noprime[i]) continue;
        for(int j = i*i; j <= 1000; j+=i){
            noprime[j] = true;
        }
    }
    
    int res = 0;
    for(int i = 0; i < n; ++i){
        int num;
        cin >> num;
        res += !noprime[num];
    }
    cout << res << '\n';
    return 0;
}