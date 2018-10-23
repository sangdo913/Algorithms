#include<iostream>
#include<vector>

using namespace std;

vector<int> v;
int n, r;
void perm(int len){
    if(len == r){
        for(int i = 0; i < r; i++){
            cout << v[i] << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i =1; i <= n; i++){
        v.push_back(i);
        perm(len + 1);
        v.pop_back();
    }
}

int BOJ15651(){
    cin >> n >> r;
    perm(0);
    return 0;
}