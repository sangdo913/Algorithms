#include<iostream>

using namespace std;

int h, w,n, info[100][2];

int check(int r1, int c1, int r2, int c2){
    int hh = r1+ r2;
    int ww = c1 > c2 ? c1 : c2;
    
    if(hh <= h && ww <= w) return r1*c1 + r2*c2;

    hh = r1 > r2 ? r1 : r2;
    ww = c1 + c2;

    if(hh <= h && ww <= w) return r1*c1 + r2*c2;

    return 0;
}

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int Do(){
    cin >> h >> w >> n;
    for(int i = 0; i < n; i++){
        cin >> info[i][0] >> info[i][1];
    }
    int res = 0;
    int temp;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            res = MAX(res, check(info[i][0], info[i][1], info[j][0], info[j][1]));
            info[i][0]^= info[i][1] ^= info[i][0] ^= info[i][1];

            res = MAX(res, check(info[i][0], info[i][1], info[j][0], info[j][1]));
            info[j][0]^= info[j][1] ^= info[j][0] ^= info[j][1];

            res = MAX(res, check(info[i][0], info[i][1], info[j][0], info[j][1]));
            info[i][0] ^= info[i][1] ^= info[i][0] ^= info[i][1];

            res = MAX(res, check(info[i][0], info[i][1], info[j][0], info[j][1]));
        }
    }
    cout << res;
    return 0;
}