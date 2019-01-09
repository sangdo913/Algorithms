//Mixing Milk
//https://www.acmicpc.net/problem/16769

#include<iostream>

using namespace std;

int C[3];
int num[3];

void move(int i, int j){
    num[j] +=num[i];
    if(C[j] < num[j]) num[i] = num[j] - C[j], num[j] = C[j];
    else num[i] = 0;
}

int Do(){
    for(int i = 0; i <3; i++) cin >> C[i] >> num[i];

    int s = 0;
    for(int i = 0; i < 100; i++,s++){
        move(s%3, (s+1)%3);
    }
    for(int i = 0; i < 3; i++) cout << num[i] << ' ';
    return 0;
}