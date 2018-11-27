#include<iostream>

using namespace std;

struct COD{
    int r, c;
};

void print(const COD& c){
    cout << c.r << ' ' << c.c << '\n';
}

int main(){
    print({1,2});

    return 0;
}