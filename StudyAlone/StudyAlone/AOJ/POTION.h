#include<iostream>

using namespace std;
int r[200], p[200];

int GCD(int a, int b){
    if(a < b) a ^= b ^= a ^= b;
    int r = a%b;
    while(r){
        a = b, b = r;
        r = a%b;
    }
    return b;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int C;

    cin >> C;
    while(C--){
        int n;
        cin >> n; 
        int g;
        for(int i = 0; i < n; ++i){ cin >> r[i]; }
        for(int i = 0; i < n; ++i) cin >> p[i];

        g = r[0];
        for(int i = 1; i +1 < n; ++i){
            g = GCD(g, r[i]); 
        }
        for(int i = 0; i < n; ++i){
            r[i] /= g;
        }
        int maxmul = 0;
        for(int i = 0; i < n; ++i){
            int mul = p[i] / r[i] + (p[i] % r[i] != 0);
            maxmul = mul < maxmul ? maxmul : mul;
        }
        for(int i = 0; i < n; ++i){
            int diff = r[i]*maxmul - p[i];
            if(diff > 0) cout << diff << ' ' ;
            else cout << 0 << ' ';
        }
        cout << '\n';
    }

    return 0;
}