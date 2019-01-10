//괄호 추가하기
//https://www.acmicpc.net/problem/16637

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int nums[21], n;
char op[20];
int order[256];

int cal(int num1, int num2, char op){
    switch(op){
        case '+': return num1 + num2;
        case'-':return num1-num2;
        case'*': return num1*num2;
    }
    return -1;
}

int cal(int bit){
    vector<int> veci;
    vector<char> vecop;

    veci.push_back(nums[0]);

    for(int i = 0; i < n/2; i++){
        if((bit & 0b11) == 0b11) return -(1<<31);
        if(bit&1){
            int num = *veci.rbegin(); veci.pop_back();
            veci.push_back(cal(num, nums[i+1], op[i]));
        }
        else{
            veci.push_back(nums[i+1]);
            vecop.push_back(op[i]);
        }

        bit>>=1;
    }

    string s;
    for(int i = 0; i < vecop.size(); i++){
        s.push_back(i);
        s.push_back(vecop[i]);
    }

    vector<int> num = veci;
    s.push_back(vecop.size());
    veci.clear();
    vecop.clear();

    string calc;

    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 0 && s[i] <= n){
            calc.push_back(s[i]);
        }
        else{
                while(vecop.size() && order[vecop.back()] >= order[s[i]]) {
                    calc.push_back(vecop.back());
                    vecop.pop_back();
                }
            vecop.push_back(s[i]);
        }
    }
    while(vecop.size()){
        calc.push_back(vecop.back()); vecop.pop_back();
    }
    
    for(int i = 0; i < calc.size(); i++){
        if(calc[i] >= 0 && calc[i] <= n){
            veci.push_back(num[calc[i]]);
        }
        else{
            int n1 = veci.back(); veci.pop_back();
            int n2 = veci.back(); veci.pop_back();
            veci.push_back(cal(n2,n1,calc[i]));
        }
    }
    int res = veci.back();
    return res;
}

int MAX(int a, int b){ return a < b ? b : a;}

int Do(){
    cin >> n;
    order['+'] = order['-'] = 0;
    order['*'] = 1;

    for(int i = 0; i < n; i+=2){
        char in;
        cin >> in;
        cin >> op[(i+1)/2];
        nums[i/2] = in-'0';
    }

    cin >> nums[n/2];

    int res = -(1 << 31);

    for(int i = 0; i < 1 << (n/2); i++){
        res = MAX(res, cal(i));
    }
    cout << res;

    return 0;
}