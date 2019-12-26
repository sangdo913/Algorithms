#include<iostream>
using namespace std;
unsigned char arr[100000];
unsigned char str[5000];
unsigned char comm[5000];
int p;
int sp;
int asize, csize, ssize;
int jump[100000];


int main(){
    int cnt;
    cin >> cnt;
    while(cnt--){
        int fcnt = 0;
        p = sp = 0;
        cin >> asize >> csize >> ssize;
        for(int i = 0; i < asize; ++i) cin >> arr[i];
        for(int i = 0; i < csize; ++i) jump[i] = -1;
        cin >> comm;
        cin >> str;
        int cp = 0;
        while(cp != csize){

        }
    }
    return 0;
}