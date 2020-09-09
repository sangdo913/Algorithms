//https://leetcode.com/problems/reaching-points/
#include<iostream>
using namespace std;

int bs(int ma, int a, int b){
    int s = 0, e = a;
    while(s<=e){
        int m = (s+e)/2;
        
        if(a-(long long)b*m > ma && a - (long long)b*m > b) s = m +1;
        else e = m-1;
    }
    return e+1;
}

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        int cnt = 100;
        while(cnt--){
            if(sx == tx && sy == ty) return 1;
            if(tx < ty){
                int s = bs(sy, ty, tx);
                ty -= tx*s;
            }
            else{
                int s = bs(sx, tx,ty);
                tx -= ty*s;
            }
        }
        return tx == sx && ty == sy;
    }
};