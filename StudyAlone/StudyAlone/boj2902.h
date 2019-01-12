#include<iostream>
#include<string>

using namespace std;

int Do(){
    string in;
    cin >> in;
    for(int i = 0; i < in.size(); i++){
        if('A'<= in[i] && in[i]<='Z'){
            cout <<in[i];
        }
    }
    return 0;
}