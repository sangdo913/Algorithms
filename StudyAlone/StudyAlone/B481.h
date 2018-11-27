#include<iostream>
#include<string>

using namespace std;

int B481(){
    string s;
    int n;
    cin >> n;
    cin >> s;
    int cnt = 0;
    int res = 0;
    for(int i = 0; i < s. size(); i++){
        if(s[i] == 'x'){
            cnt++;
            if(cnt == 3){
               res++; 
               cnt = 2;
            }
        }
        else cnt = 0;
    }
    cout << res;
    return 0;
}