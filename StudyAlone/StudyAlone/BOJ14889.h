#include<iostream>

using namespace std;

int ABS(int i1){return i1 > 0 ? i1 : -i1;}
int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}

int arr[20][20], n;

int f(int selected){
    int team[2] = {0,0};
    for(int i = 0; i < n; i++){
        bool t1 = selected & (1 << i); 
        for(int j = i + 1; j < n; j++){
            bool t2 = selected & (1<<j);
            if(t1 == t2){
                team[t1]+= arr[i][j] + arr[j][i];
            }
        }
    }
    return ABS(team[0]-team[1]);
}

int getZero(int bit){
    int res = 0;
    while((bit & 1) == 0) res++, bit >>= 1;
    return res;
}

int Do(){
    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> arr[i][j];

    int bit = (1 << (n/2))-1;
    int res = 0x7fffffff;

    while(bit < (1 << n)){
        int temp = bit | ((-bit & bit)-1);
        res = MIN(f(bit), res); 
        
        int nextBit = (temp + 1) | (((~temp & -~temp) -1 ) >> (getZero(bit)+1));
        bit = nextBit;
    }

    cout << res;
    return 0;
}