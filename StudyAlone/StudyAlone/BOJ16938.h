#include<iostream>

using namespace std;

int difficulty[15], n, l, r, x;

bool check(int bit){
    int num = 0, idx = 0;
    int MIN = 0x3f3f3f3f;
    int score = 0;
    int MAX = 0;

    while(bit){
        if(bit&1){
            score += difficulty[idx];
            MIN = MIN > difficulty[idx] ? difficulty[idx] : MIN;
            MAX = MAX < difficulty[idx] ? difficulty[idx] : MAX;
            num++;
        }
        bit>>=1;
        idx++;
    }
    return num > 1 && l <= score && score <= r && (MAX - MIN >= x);
}

int Do(){
    cin >> n >> l >> r  >> x;
    for(int i = 0; i < n; i++) cin >> difficulty[i];

    int res = 0;

    for(int b = 1; b < (1 << n); b++) 
        res += check(b);

    cout << res;

    return 0;
}