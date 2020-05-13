#include<iostream>
#include<string>

using namespace std;
string sudoku[9];

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        for(int i = 0; i < 9 ;++i) cin >> sudoku[i];
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(sudoku[i][j] == '1'){
                    sudoku[i][j/3*3 + (j+1)%3] = '1';
                    break;
                }
            }
        }
        for(int i = 0; i < 9 ;++i) cout << sudoku[i] << '\n';
    }
    return 0;
}