#include<iostream>
#include<vector>

using namespace std;

int n, r;
vector<bool> flag;

void comb(int len, int selected){
    if(selected == r){
        for(int i = 0 ; i< n; i++){
            if(flag[i] == true){
                cout << i+1 << ' ';
            }
        }
        cout << '\n';
        return;
    }

    if(len == n) return;

    flag[len] =true;
    comb(len+1, selected+1);
    flag[len] = false;
    
    comb(len +1, selected);
}

int BOJ15649(){
    cin >> n >> r;
    flag.resize(n);

    comb(0,0);
    return 0;
}