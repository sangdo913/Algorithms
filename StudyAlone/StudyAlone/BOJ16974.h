#include<iostream>

using namespace std;

long long patty[51];
long long hsize[51];

long long get(int level, long long remain){
    long long res = 0;
    if(level == 0) return 1;
    if(remain == 1) return 0;
    --remain;
    if(remain <= hsize[level-1]) return get(level-1, remain);
    
    remain -= hsize[level-1];
    res += patty[level-1];
    if(remain == 1) return res+1;
    res++;
    --remain;

    if(remain <= hsize[level-1]) return res + get(level-1, remain);
    return res + patty[level-1];
}

int Do(){
    patty[0] = 1;
    hsize[0] = 1;

    for(int i = 1; i <= 50; i++){
        patty[i] = (1LL << (i+1)) -1;
        hsize[i] =  (1LL << (i+2)) -3;
    }
    
    int n; long long x;
    cin >> n >> x;
    cout << get(n,x);
    return 0;
}
