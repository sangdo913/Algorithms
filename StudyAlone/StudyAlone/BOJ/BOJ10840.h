#include<iostream>
#include<string>
using namespace std;
int cnt[26][1501];
int cnt2[26][1501];

char a[1501],b[1501];;
int asize, bsize;
bool parametric(int ii, int jj, int l){
    if(!l) return true;
    for(int i = 0; i < 26; ++i){
        int num1 = cnt[i][ii+l-1] - cnt[i][ii-1];
        int num2 = cnt2[i][jj+l-1] - cnt2[i][jj-1];
        if(num1!=num2) return false;
    }
    return true;
}

int bs(int i, int j){
    int aremain = asize - i+1;
    int bremain = bsize - j+1;
    int s = 0, e = aremain < bremain ? aremain : bremain;
    while(s <= e){
        int m = (s+e)/2;
        if(parametric(i,j,m)) s = m + 1;
        else e = m-1;
    }
    return e;
}

int main(){
    freopen("0Text.txt", "r",stdin);
    cin >> a+1 >> b+1;
    while(a[asize+1]) asize++;
    while(b[bsize+1]) bsize++;
    for(int i = 1; i<= asize; ++i){
        for(int j = 0; j < 26; ++j){
            cnt[j][i] += cnt[j][i-1];
        }
        cnt[a[i]-'a'][i]++;
    }
    for(int i = 1; i <= bsize; ++i){
        for(int j = 0; j < 26; ++j){
            cnt2[j][i] += cnt2[j][i-1];
        }
        cnt2[b[i]-'a'][i]++;
    }
    int res = 0;
    for(int i = 1; i <= asize; ++i){
        for(int j = 1; j <= bsize; ++j){
            int ret= bs(i,j);
            if(ret > res) res = ret;
        }
    }
    
    cout << res;
    return 0;
}