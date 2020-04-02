#include<iostream>
#include<string>

using namespace std;

char num[64][65];

 string merge(int sr, int sc, int size){
    string res("");
    int cnt1 = size, cnt2 = size;
    char n = num[sr][sc];
    int c = sc;
    int r = sr;
    bool fail = false;
    while(cnt1--){
        cnt2 = size;
        c = sc;
        while(cnt2--){
            if(n != num[r][c]){
                fail = true;
                goto END;
            }
            c++;
        }
        r++;
    }
    END:
    if(fail){
        res.push_back('(');
        size>>=1;
        res += merge(sr, sc, size);
        res += merge(sr, sc+size, size);
        res += merge(sr+size, sc,size);
        res += merge(sr+size, sc+size, size);
        res.push_back(')');
    }
    else{
        res.push_back(n);
    }
    return res;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> num[i];
    }
    cout << merge(0,0,n);

    return 0;
}