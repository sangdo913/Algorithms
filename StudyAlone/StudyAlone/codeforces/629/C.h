#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt","r",stdin);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string in;
        cin >> in;
        bool isbig = false;
        string big("1"), small("1");
        for(int i = 1; i < n; ++i){
            if(in[i] == '0'){
                big.push_back('0');
                small.push_back('0');
            }
            else if(in[i] == '2'){
                if(isbig){
                    big.push_back('0');
                    small.push_back('2');
                }
                else{
                    big.push_back('1');
                    small.push_back('1');
                }
            }
            else{
                if(isbig){
                    big.push_back('0');
                    small.push_back('1');
                }
                else{
                    isbig = true;
                    big.push_back('1');
                    small.push_back('0');
                }
            }
        }
        cout << big << endl << small << endl;
    }
    return 0;
}