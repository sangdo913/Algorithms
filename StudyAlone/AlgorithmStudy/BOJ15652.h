#include<iostream>
#include<vector>

using namespace std;

int n,r;
vector<int> v;
void comb(int len, int sel){
    if(len == r){
        for(int i = 0;  i < len ; i++){
            cout << v[i] << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i = sel; i <= n; i++){
        v.push_back(i);
        comb(len + 1, i);
        v.pop_back();
    }

}
int BOJ15652(){
    cin >> n >> r;
    
    comb(0, 1);

    return 0;
}