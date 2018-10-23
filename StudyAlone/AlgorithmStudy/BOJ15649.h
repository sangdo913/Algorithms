#include<iostream>
#include<vector>

using namespace std;

vector<int> v;

void swap(int &a, int &b){
    int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void rotater(int a, int b){
    int temp = v[b];
    for(int i = b; i > a; i--){
        v[i] = v[i-1];
    }
    v[a] = temp;
}

void rotatel(int a, int b){
    int temp = v[a];
    for(int i = a; i < b; i++){
        v[i] = v[i+1];
    }
    v[b] = temp;
}


int n, r;
void perm(int len){
    if(len == r){
        for(int i = 0; i < r; i++){
            cout << v[i] << ' '; 
        }
        cout << '\n';
        return;
    }

    for(int i = len; i < n; i++){
        rotater(len, i);
        perm(len+1);
        rotatel(len, i);
    }
}

int BOJ15649(){
    cin >> n >> r;

    for(int i = 0; i < n; i++){
        v.push_back(i+1);
    }
    perm(0);
    return 0;
}