///¾ËÆÄºª Ã£±â
//https://www.acmicpc.net/problem/10809
#include<iostream>
#include<string>

using namespace std;
int check['Z'-'A'+1];

int Do(){
    string s;
    cin >> s;

    for(int i = 0; i < 'Z'-'A'+1; i++){
        check[i] = -1;
    }

    for(int i = 0; i < s.size(); i++){
        if(check[s[i]-'a'] == -1) check[s[i]-'a'] = i; 
    }

    for(int i = 0; i < 'z'-'a' + 1; i++) cout << check[i] << ' ';
    return 0;
}