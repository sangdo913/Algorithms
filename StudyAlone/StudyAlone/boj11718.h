#include<iostream>
#include<string>

using namespace std;

int Do(){
    string s;
    while(getline(cin,s)){
        cout << s << '\n';
    }

    return 0;
}