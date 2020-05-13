#include<iostream>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int T;
    cin >> T;
    for(int tc = 0; tc < T; ++tc){
        int n;
        cin >> n;
        int a, b, c;
        bool notfind = true;
        for(long long i = 2; i *i <= n; ++i){
            if(n%i == 0){
                a = i;
                n/= a;
                notfind = false;
                break;
            }
        }
        if(notfind) goto END;
        notfind = true;
        for(long long i = a+1; i *i <= n; ++i){
            if(n%i == 0){
                b = i;
                n/= b;
                notfind = false;
                break;
            }
        }
        if(notfind) goto END;
        notfind = n <= b;
        END:
        if(!notfind){
            cout << "YES\n";
            cout << a <<  ' ' << b << ' ' << n <<'\n';
        }
        else cout <<"NO\n";
    }
    return 0;
}