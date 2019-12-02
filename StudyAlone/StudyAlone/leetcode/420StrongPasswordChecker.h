#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> memoi[21][3][8];
string s;

int dp(int size, int len, int cont,int check, char before){
    if(size > 20) return 0x3f3f3f3f;
    if(len == s.size()){
        if(size < 6) return 0x3f3f3f3f;
        if(check != 0b111) return 0x3f3f3f3f;
        return 0;
    }
    int delcont = cont;
    char delbefore = before;
    if(before == s[len]) cont++;
    else cont = 0, before = s[len];

    if(memoi[size][cont][check][len] != -1) return memoi[size][cont][check][len];
    int &res = memoi[size][cont][check][len];
    res = 0x3f3f3f3f;

    if(cont != 2){
        int nextcheck = check;
        if('a' <= s[len] && s[len] <= 'z') nextcheck |= (1<<2);
        else if('A' <= s[len] && s[len] <='Z') nextcheck |= (1<<1);
        else if('0' <= s[len] && s[len] <= '9') nextcheck |= (1<<0);
        res = dp(size+1, len+1, cont, nextcheck, s[len]);
    }
    int temp;
    for(int i = 0; i < 3; ++i){
        temp = dp(size+1, len, 0, check | (1 << i), -1) + 1;
        res = temp < res ? temp : res;

        temp = dp(size+1, len+1, 0, check | (1 <<i ), -1) + 1;
        res = temp < res ? temp : res;

    }
    temp = dp(size, len+1, delcont, check, delbefore)+1;
    res = temp < res ? temp : res;
    return res;
}

class Solution {
public:
    int strongPasswordChecker(string str) {
        for(int i = 0; i < 21; ++i) for(int j = 0; j < 3; ++j) for(int k = 0; k < 8; ++k) memoi[i][j]
        [k].clear(), memoi[i][j][k].resize(str.size()+1, -1);
        s = str;
        if(!str.size()) return 6;

        return dp(0,0,0,0,-1);
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    string s;
    cin >> s;
    cout << Solution().strongPasswordChecker(s) << endl;
    return 0;
}
