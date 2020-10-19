#include<iostream>
using namespace std;

bool parametric(long long n, long long s, long long pl){
    long long num = n + pl;
    int digit = 0;
    while(num){
        if(num%10){
            digit++;
        }
        num /= 10;
    }
    return digit <= s;
}

int getdigit(long long n){
    int ret = 0;
    while(n){
        ret += n%10;
        n/=10;
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        long long n,s;
        cin >> n >> s;
        int cnt = 0;
        long long digit = 10;
        long long pl = 0;
        while(getdigit(n) > s){
            long long remain = (n%digit);
            n += digit-remain;
            pl += digit-remain;
            digit*=10;
        }
        cout << pl << endl;
    }

    return 0;
}