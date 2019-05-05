#include<iostream>

using namespace std;

int n, m, k;

int gcd(int a, int b){
    a = a < b? a^=b^=a^=b : a;

    int r;

    while(b){
        r = a%b;
        a = b;
        b = r;
    }
   return a;
}

#define ABS(x) ((x) > 0 ? (x) : -(x))

int Do(){
    int res = 0;
    cin >> n >> m >> k;
    for(int i  =0;i  <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int i2 = 0; i2 <= n; i2++){
                for(int j2 = 0; j2 <= m ; j2++){
                    if(i == i2 && j == j2) continue;
                    if(i ==i2 || j == j2) {
                        res += ABS(i-i2) + ABS(j-j2) == k-1;
                        continue;
                    }

                    int g = gcd(ABS(i2- i), ABS(j2 - j));
                    int x = ABS(i2-i)/g;

                    res += ABS(i2-i)/x == k-1;
                }
            }
        }
    }
    cout << res/2;
    return 0;
}
