#include<iostream>
#include<string>

using namespace std;

long long dnum[100001];
string getstring(int n,int bn,long long remain){
    if(bn == 2){
        if(dnum[n-1] >= remain) return string("a") + getstring(n-1, bn, remain);
        else return string("b") + getstring(n-1, 1, remain - dnum[n-1]);
    }
    if(bn == 1){
        string res(n,'a');
        res[res.size()-remain] = 'b';
        return res;
    }
    return "";
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    dnum[2] = 1;
    for(int i = 3; i <= 100000; ++i){
        dnum[i] += dnum[i-1]+i-1;
        if(dnum[i] < 0) cout << dnum[i] << endl;
    }
    while(n--){
        int a, b;
        cin >> a >> b;
        cout << getstring(a, 2, b) <<endl;
    }
    return 0;
}