#include<iostream>
#include<cstring>

using namespace std;

int sw[2000][2000];
int slen[2000];

int cnt[2000];
int temp[2000];

int Do(){
    int n , m;
    cin >> n >> m;
    for(int i  =0; i < n; i++){
        cin >> slen[i];
        for(int j  =0; j < slen[i]; j++){
            cin >> sw[i][j];
            --sw[i][j];
            ++cnt[sw[i][j]];
        }
    }

    for(int i = 0; i < n; i++){
        memcpy(temp, cnt, sizeof(cnt));
        bool ch = true;
        for(int j = 0; j < slen[i]; j++){
            --temp[sw[i][j]];  
            if(temp[sw[i][j]] == 0) {ch = false; break;}
        }
        if(ch) return!(cout << 1);
    }
    cout << 0;

    return 0;
}