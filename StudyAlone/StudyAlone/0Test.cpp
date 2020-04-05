#include<iostream>
#include<string>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    string input;
    cin >> input;
    int n;
    int j = 0;
    int checknum = 0;
    int res = 0;
    for(int i = 0; i < input.size();++i){
        while(j < input.size() && ((input[j] =='1') || (input[j] == '0' && checknum < n))){
            ++j;
            if(input[j] == '0') checknum++;
        }
        if(res < j - i) res = j-i;
        if(input[i] == '0') checknum--;
    }
    cout << res;
    return 0;
}