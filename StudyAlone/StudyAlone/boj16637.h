//괄호 추가하기
//https://www.acmicpc.net/problem/16637

#include<iostream>
#include<vector>

using namespace std;


int nums[21], n;
char op[20];

int cal(int num1, int num2, char op){
    switch(op){
        case '+': return num1 + num2;
        case'-':return num1-num2;
        case'*': return num1*num2;
    }
}

int cal(int bit){
    vector<int> veci;
    vector<char> vecop;

    for(int i = 0; i < n/2; i++){
        if(bit & 0b11 == 0b11) return -(1<<31);
        if(bit&1){
            veci.push_back(cal(nums[i], nums[i+1], op[i]));
            vecop.push_back(op[i+1]);
            i++;
        }
        else{
            veci.push_back(nums[i]);
            vecop.push_back(op[i]);
        }
    }
}

int MAX(int a, int b){ return a < b ? b : a;}

int Do(){
    cin >> n;

    for(int i = 0; i < n; i+=2){
        cin >> nums[i];
        cin >> op[i+1];
    }
    cin >> nums[n/2];
    op[n/2] = '+';

    int res = -(1 << 31);
    for(int i = 0; i < 1 << (n/2); i++){
        res = MAX(res, cal(i));
    }
    cout << res;

    return 0;
}