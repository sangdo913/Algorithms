#include<iostream>

using namespace std;
int n;
int myarr[5000];
int temp[5000];
int changed[5000];

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char in;
        cin >> in;
        myarr[i] = in == 'B';
    }

    int res = 0x3f3f3f3f;
    int res2 = -1;
    for(int k = 1; k <= n; ++k){
        for(int i = 0; i < n; ++i) changed[i] = 0;
        int cnt = 0;
        int d = 1;
        for(int j = 0; j < n; ++j) {
            if(changed[j]){
                d ^=1;
            }
            if(d == myarr[j]) {
                if(n - k < j) goto NEXT;
                if(k + j < n) changed[k+j]^= 1;
                d^=1;
                cnt++;
            }
        }

        if(res > cnt) {
            res = cnt;
            res2 = k;
        }
        
        NEXT:
        int x = 1;
    }
    cout << res2 << ' ' << res;
    return 0;
}