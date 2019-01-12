//문자열 반복
//https://www.acmicpc.net/problem/2675
#include<iostream>
#include<string>

using namespace std;

int Do(){
    int c, n;
    string s;

    cin >> c;

    while(c--){
        cin >> n >> s;

        for(int sz = 0; sz < s.size(); sz++)
        for(int i = 0; i < n; i++){
            cout << s[sz];
        }
        cout << '\n';
    }
    return 0;
}