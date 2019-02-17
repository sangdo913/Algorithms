#include<iostream>
using namespace std;

char str[28];
bool check[256];
int len;

int Do(){
    cin >> str;
    while(str[len]){
        check[str[len]] = true;
        len++;
    } 
    str[len] = 'a'-1;

    while(len){
        for(int i = str[len] + 1; i<='z'; i++){
            if(!check[i]){
                str[len] = i;
                str[len+1] = 0;
                return !(cout << str);
            }
        }

        check[str[--len]] = false;  
    }
    
    cout << -1;
    return 0;
}
