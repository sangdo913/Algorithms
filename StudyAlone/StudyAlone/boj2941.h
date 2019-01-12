#include<iostream>
#include<string>

using namespace std;

string check[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};

int Do(){
    string in;
    cin >> in;

    int res = 0;

    for(int i = 0; i < in.size(); i++){
        int j= 0;
        for(; j < 8; j++){
            if(check[j] == string(in.begin() + i, in.begin() + i + check[j].size())){
                res++, i += check[j].size()-1;
                break;
            }
        }
        res += j == 8;
    }
    cout << res;
    return 0;
}