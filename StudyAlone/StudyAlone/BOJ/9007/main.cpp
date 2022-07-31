//BOJ9007
#include<iostream>
#include<fstream>
int arr[4][1000];
int merge[2][1000000];
using namespace std;

int main() {
    int t,k,n;
    cin >> t;
    
    for(int i = 0; i < t ; ++i) {
        cin >> k >> n;
        for(int j = 0; j < 4; ++j) {
            for(int i = 0; i < n; ++i) {
                cin >> arr[j][i];
            }
        }
        for(int l = 0; l < 2; ++l) {
            for(int i = 0;i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    merge[l][i] = arr[l*2][i]+arr[l*2+1][j];
                }
            }
        }
        //debug
        for(int i = 0; i < 2; ++i) {
            for(int j = 0 ; j< n*n; ++j) {
                cout << merge[i][j] << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}