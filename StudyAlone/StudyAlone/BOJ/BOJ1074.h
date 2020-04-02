#include<iostream>

using namespace std;

int merge(int dr, int dc, int sr, int sc, int size){
    if(size == 1) return 0;
    int ss = size/2*size/2;
    int order = 0;
    if(dr < sr+ size/2 && dc < sc + size/2){
        return order+ merge(dr,dc, sr, sc,size/2);
    }
    order += ss;
    if(dr < sr +size/2) return order+ merge(dr,dc,sr, sc+size/2, size/2);
    order += ss;
    if(dc < sc + size/2) return order + merge(dr,dc,sr + size/2, sc, size/2);
    order += ss;
    return order + merge(dr,dc, sr+size/2, sc+size/2, size/2);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, r, c;
    cin >> n >> r >> c;
    n = 1 << n;

    cout << merge(r,c,0,0,n);
    return 0;
}