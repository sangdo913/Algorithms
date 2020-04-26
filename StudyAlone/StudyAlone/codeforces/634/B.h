#include<iostream>
#include <string>
using namespace std;

int main(){
    int t;
    freopen("0Text.txt", "r",stdin);
    cin >> t;
    while(t--){
        int n,a,b;
        string str;
        cin >> n >> a >> b;
        for(int i = 0; i < a-b; ++i){
            str.push_back('a');
        }
        for(int i = 0; i < b; ++i) str.push_back(i+'a');
        while(str.size() != n){
            str.push_back(str[str.size()-a]);
        }
        cout << str <<'\n';
    }
    
    return 0;
}