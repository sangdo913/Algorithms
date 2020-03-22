#include<iostream>
#include<algorithm>

using namespace std;

int n;
int arr[5][20000];
int getcnt[20000][5];
int compression[20000];
int order[20000];

struct cmp{
    bool operator() (int a, int b){
        int cnt = 0;
        for(int i = 0; i < 5; ++i){
          cnt += getcnt[a][i] < getcnt[b][i];
        }
        return cnt >= 3;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < n; ++j){
            cin >> arr[i][j];
            compression[j] = arr[i][j];
        }
    }

    sort(compression, compression + n);
    
    for(int i = 0; i < 5; ++i){
       for(int j  = 0; j < n; ++j) {
           int idx = find(compression, compression + n, arr[i][j]) - compression;
           getcnt[idx][i] = j;
       } 
    }

    for(int i = 0; i < n; ++i) order[i] = i;
    sort(order, order + n, cmp());
    for(int i = 0; i < n; ++i) cout << compression[order[i]] << ' ';

    return 0;
}