#include<iostream>

using namespace std;

int gcd(int a, int b){
    if(a < b) a^=b^=a^=b;
    int r = a%b;
    while(r){
        a =b, b= r, r= a%b;
    }
    return b;
}

int nums[100];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        int nn;
        cin >> nn;
        for(int i = 0; i < nn; ++i){
            cin >> nums[i];
        }

        long long res = 0;
        for(int i = 0; i < nn; ++i){
            for(int j = i + 1; j < nn; ++j){
                res += gcd(nums[i], nums[j]);
            }
        }
        cout << res << '\n';
    }
    return 0;
}