#include<iostream>
#include<string>

using namespace std;

int Do(){
    string s;
    while(true){
        getline(cin, s);
        if(s == string("END")) return 0;
        cout << string(s.rbegin(), s.rend()) << '\n';
    }
    return 0;
}