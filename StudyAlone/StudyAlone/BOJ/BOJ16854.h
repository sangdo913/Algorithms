#include<iostream>
#include<string>
#include<queue>

using namespace std;

string str;
char p[256];

int main() {
    freopen("0Text.txt", "r", stdin);
    p['('] = ')';
    p[')'] = '(';
    cin >> str;
    int res = 0;

    for(int i = 0; i < str.size()-1; ++i){ 
        int num = 0;
        for(int l = 0; i - l >= 0 && i + l +1 < str.size() && str[i-l] == p[str[i+l+1]]; ++l){
            if(str[i-l] == ')'){
                num++;
            }
            else if(num > 0) num--;
            // if(!num){
            //     cout << i-l << ' ' << i + l + 1 << endl;
            //     for(int j = i-l; j <= i + l + 1; ++j){
            //         cout << str[j];
            //     }
            //     cout << endl;
            // }
            res += !num;
        }
    }
    cout << res;
    return 0;
}