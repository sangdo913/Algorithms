#include<iostream>

using namespace std;

int getBit(int x){
    int res = 0;
    while(x){
        if(x&1)res++;
        x>>=1;
    }
    return res;
}

int codeforcesB(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int bit = getBit(n);
        cout << (1 << bit) << '\n';
    } 
    return 0;
}