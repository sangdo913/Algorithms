#include<iostream>
#include<string>

using namespace std;

bool type[4];

char conv[256];int len;
string in;

int Do(){
    for(int i = 'a'; i <='z'; i++){
        conv[i] = 0;
    }

    for(int i = 'A'; i <= 'Z'; i++) conv[i] = 1;
    for(int i = '0'; i <='9'; i++) conv[i] = 2;
    conv['!'] = conv['@'] = conv['#'] = conv['$'] = conv['%'] = conv['^'] = conv['&'] = conv['*'] = conv['('] = conv[')'] = conv['-'] = conv['+'] = 3;

    cin >> len >> in;

    for(int i = 0; i < len; i++) type[conv[in[i]]] = true;

    int res = 6 - len;
    int blank = 0;
    for(int i = 0; i < 4; i++) blank += !type[i];
    cout << (res > blank ? res : blank);
    return 0;
}