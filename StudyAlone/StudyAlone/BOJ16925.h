#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int len;
string info[99*2];
char res[99*2];
string str;

int store[100][2];
bool check[100];

bool canmake(int n){
    int idx1 = store[len-1][n];
    int idx2 = store[len-1][n^1];
    res[idx1] = 'P';
    res[idx2] = 'S';

    for(int i = 1; i < len-1; i++){
        int ch = 0;
        int idx = store[i][ch];

        string ss1 = string(info[idx1].begin(), info[idx1].begin() + i);
        string ss2 = string(info[idx2].rbegin(), info[idx2].rbegin() + i); 
        ss2 = string(ss2.rbegin(), ss2.rend());

        bool res1 = ss1 == info[store[i][0]] && ss2 == info[store[i][1]];
        bool res2 = ss1 == info[store[i][1]] && ss2 == info[store[i][0]];

        if(res1){
            res[store[i][0]] = 'P';
            res[store[i][1]] = 'S';
        }
        else if(res2){
            res[store[i][1]] = 'P';
            res[store[i][0]] = 'S';
        }
        else return false;
    }
    return true;
}

int Do(){
    cin >> len;
    for(int i = 0; i < 2*(len-1); i++){
        cin >> info[i];
        int l = info[i].size();

        store[l][check[l]] = i;
        check[l] = true;
    }

    str.resize(len);

    if(canmake(0)){
        int p = store[len-1][res[store[len-1][1]] == 'P'];
        int s = store[1][res[store[1][1]] == 'S'];
        cout << info[p] << info[s]<<'\n';
        cout << res;
    }

    else if(canmake(1)){
        int p = store[len-1][res[store[len-1][1]] == 'P'];
        int s = store[1][res[store[1][1]] == 'S'];
        cout << info[p] << info[s]<<'\n';
        cout << res;
    }
    else{
        cout << "wrong";
    }
    
    return 0;
}