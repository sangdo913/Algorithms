/*
#include<iostream>

using namespace std;

int n;
int info[16][16];

int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}

int res = 0x3f3f3f3f;

int ABS(int i){return i > 0 ? i : -i;}

void comb(int cnt, int len, int visit){
    if(len == n) return;

    if(n/2 == cnt){
        int a = 0, b = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                if((visit & (1<<i)) && (visit & (1<<j))){
                    a+= info[i][j];
                                    
                }
                else if ((visit & (1 << i)) == 0 && ((visit &(1 << j)) == 0)){
                    b+= info[i][j];
                }
            }
        }
        int sub = ABS(a - b);
        res = MIN(sub,res);
        return;
    }

    comb(cnt+1, len+1, visit | 1 << len);
    comb(cnt, len+1, visit);
}

int SWEA4012(){
    int t;
    cin>> t;
    for(int tc= 1; tc  <= t; tc++){
        cin >> n;

        res = 0x3f3f3f3f;

        for(int i = 0; i <n;i++){
            for(int j =0; j < n; j++){
                cin >> info[i][j];
            }
        }

        comb(0, 0, 0);

        cout << '#' << tc << ' ' << res << '\n';
    }

    return 0;
}
*/

#include<iostream>

using namespace std;

int n;
int info[16][16];

int getZero(int i){
    int res = 0;

    while(i){
        res++;
        i>>=1;
    }

    return res; 
}

int SWEA4012(){
    int t;
    cin >> t;

    for(int tc = 1; tc <= t; tc++){
        cin >> n;
        
        int cnt = n /2;

        int bit = 1 << cnt;

        while(bit < ( 1 << n)){
            int temp = (bit+1);
        }
    }
    return 0;
}