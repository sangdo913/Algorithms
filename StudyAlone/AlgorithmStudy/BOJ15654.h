#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v;
int n, r;
void rotateR(int a, int b){
    int temp = v[b];
    
    for(int i = b; i > a ; i--){
        v[i] = v[i-1];
    }
    v[a] = temp;
}


void rotateL(int a, int b){
    int temp = v[a];
    for(int i = a; i < b; i++){
        v[i] = v[i+1];
    }
    v[b] = temp;
}

void perm(int len ){
    if(len == r){
        for(int i = 0; i < len; i++){
            cout <<  v[i] << ' ';
        }
        cout << endl;
        return;
    }

    for(int i = len; i< v.size(); i++){
        rotateR(len, i);
        perm(len+1);
        rotateL(len, i);
    }
}
int BOJ15654(){
    cin >> n >> r;
    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        v.push_back(num);
    }
    sort(v.begin(), v.end());
    perm(0);
    return 0;
}